
# React Mastery Problems — 60+ Complex Scenarios

> A complete problem set covering hooks, rendering, closures, Redux, API calls, performance, patterns, and architecture. Solve each before reading the answer.

---

## Table of Contents

1. [Render & Effect Chain](#render--effect-chain)
2. [Closure & Stale State](#closure--stale-state)
3. [Memoization & Performance](#memoization--performance)
4. [Redux & State Management](#redux--state-management)
5. [API Calls & Async Patterns](#api-calls--async-patterns)
6. [Advanced Hooks](#advanced-hooks)
7. [Context & Composition](#context--composition)
8. [Architecture & Patterns](#architecture--patterns)

---

## Render & Effect Chain

---

### Problem 1 — Basic Render Chain

```jsx
function App() {
  const [count, setCount] = React.useState(0);
  console.log("RENDER");

  React.useEffect(() => {
    console.log("EFFECT A");
    setCount(1);
  }, []);

  React.useEffect(() => {
    console.log("EFFECT B");
  }, [count]);

  return <h1>{count}</h1>;
}
```

**Questions:**
- Exact console order?
- Total renders?
- Final UI?

<details>
<summary>Answer</summary>

**Console order:**
```
RENDER        ← initial render (count=0)
EFFECT A      ← [] fires after first paint
EFFECT B      ← [count] fires (count changed 0→1)
RENDER        ← re-render from setCount(1)
EFFECT B      ← [count] fires again (count=1)
```

**Total renders:** 2

**Final UI:** `<h1>1</h1>`

**Key insight:** Both effects run after the first render. EFFECT A calls `setCount(1)`, which triggers a re-render. On the second render, only EFFECT B runs (its dep `count` changed). EFFECT A does NOT re-run (dep `[]`).

</details>

---

### Problem 2 — Infinite Loop Detection

```jsx
function App() {
  const [user, setUser] = React.useState({});
  console.log("RENDER");

  React.useEffect(() => {
    console.log("EFFECT");
    setUser({});
  }, [user]);

  return <div>Hello</div>;
}
```

**Questions:**
- Why infinite loop?
- Which line causes the reference change?
- How to fix?

<details>
<summary>Answer</summary>

**Why infinite:** `{}` is a new object reference every render. `[user]` dependency uses `Object.is()` comparison — two different `{}` objects are never equal, so the effect fires every time, calling `setUser({})`, which triggers re-render, which fires effect again → infinite.

**Culprit line:** `setUser({})` — creates a new object reference each call.

**Fixes:**
```jsx
// Fix 1: Empty dep array (run once)
React.useEffect(() => { setUser({}); }, []);

// Fix 2: Stable primitive as dep
React.useEffect(() => { setUser({}); }, [user.id]);

// Fix 3: Compare specific fields
React.useEffect(() => { ... }, [user.name, user.email]);
```

</details>

---

### Problem 3 — useMemo Trap

```jsx
function App() {
  const [count, setCount] = React.useState(0);
  const [text, setText] = React.useState("");
  console.log("RENDER");

  const expensive = React.useMemo(() => {
    console.log("MEMO");
    return count * 10;
  }, [count]);

  return (
    <>
      <input value={text} onChange={e => setText(e.target.value)} />
      <button onClick={() => setCount(count + 1)}>Add</button>
      <h1>{expensive}</h1>
    </>
  );
}
```

**Scenario:** Type "abc", then click button once.

**Questions:**
- Console order?
- When does memo rerun?
- Total renders?

<details>
<summary>Answer</summary>

**Typing "a", "b", "c":**
```
RENDER   ← 'a' typed (text changed, count unchanged)
RENDER   ← 'b' typed
RENDER   ← 'c' typed
```
(MEMO does NOT log — count hasn't changed)

**Click button:**
```
RENDER   ← count changed (0→1)
MEMO     ← count dep changed, recomputes
```

**Total renders:** 4 (3 from typing + 1 from button)

**Memo reruns:** Only when `count` changes, not on `text` changes. This is the point of useMemo — skip expensive computation when unrelated state changes.

</details>

---

### Problem 4 — Multiple Effects Interacting

```jsx
function App() {
  const [search, setSearch] = React.useState("");
  const [page, setPage] = React.useState(5);
  console.log("RENDER");

  React.useEffect(() => {
    console.log("RESET PAGE");
    setPage(1);
  }, [search]);

  React.useEffect(() => {
    console.log("FETCH DATA", page, search);
  }, [page, search]);

  return (
    <button onClick={() => setSearch("react")}>Search</button>
  );
}
```

**After button click, what are:**
- Total renders?
- Exact logs?
- Why fetch happens twice?

<details>
<summary>Answer</summary>

**Full log sequence:**
```
RENDER               ← initial (search="", page=5)
RESET PAGE           ← search dep fires (search="")
FETCH DATA 5 ""      ← page+search dep fires

--- button clicked ---

RENDER               ← search changed to "react"
RESET PAGE           ← search changed → setPage(1)
FETCH DATA 5 "react" ← search changed, page still 5 in THIS render
RENDER               ← page changed to 1
FETCH DATA 1 "react" ← page changed
```

**Total renders:** 3 (initial + search change + page change)

**Why twice:** React batches the render but effects see the state values at render time. First fetch sees page=5 (stale), second fetch sees page=1 (correct). Senior fix: debounce, or derive page from search instead of setState.

</details>

---

### Problem 5 — Child Re-render with React.memo

```jsx
const Child = React.memo(({ onClick }) => {
  console.log("CHILD RENDER");
  return <button onClick={onClick}>Click</button>;
});

function App() {
  const [count, setCount] = React.useState(0);
  console.log("PARENT RENDER");

  const handleClick = () => console.log("clicked");

  return (
    <>
      <Child onClick={handleClick} />
      <button onClick={() => setCount(count + 1)}>Add</button>
    </>
  );
}
```

**Questions:**
- Does child rerender on count change?
- Why?
- How to fix?

<details>
<summary>Answer</summary>

**Yes, Child re-renders on every count change.**

**Why:** `handleClick` is recreated on every render — it's a new function reference each time. `React.memo` uses shallow comparison. Even though the function body is identical, `prevOnClick !== nextOnClick`, so memo considers it changed.

**Fix:**
```jsx
const handleClick = React.useCallback(() => {
  console.log("clicked");
}, []); // stable reference, no deps needed
```

Now `handleClick` reference is stable, `React.memo` correctly bails out, and Child only renders once.

</details>

---

### Problem 6 — Dangerous Closure / Stale Interval

```jsx
function App() {
  const [count, setCount] = React.useState(0);

  React.useEffect(() => {
    const id = setInterval(() => {
      console.log(count);
    }, 1000);
    return () => clearInterval(id);
  }, []);

  return (
    <button onClick={() => setCount(count + 1)}>Add</button>
  );
}
```

**Questions:**
- What logs after multiple clicks?
- Why stale closure?
- Fix?

<details>
<summary>Answer</summary>

**Always logs `0`**, regardless of how many times you click.

**Why:** The effect runs once (`[]`). The `setInterval` callback closes over `count` at the time the effect ran — which was `0`. The closure captures that value permanently. Subsequent state updates create new `count` values, but the interval's closure still points to the original `0`.

**Fix 1 — useRef:**
```jsx
const countRef = React.useRef(count);
countRef.current = count;

React.useEffect(() => {
  const id = setInterval(() => console.log(countRef.current), 1000);
  return () => clearInterval(id);
}, []);
```

**Fix 2 — functional update:**
```jsx
React.useEffect(() => {
  const id = setInterval(() => {
    setCount(c => { console.log(c); return c; });
  }, 1000);
  return () => clearInterval(id);
}, []);
```

</details>

---

### Problem 7 — Render Waterfall

```jsx
function App() {
  const [a, setA] = React.useState(0);
  const [b, setB] = React.useState(0);
  console.log("RENDER");

  React.useEffect(() => {
    console.log("EFFECT A");
    if (a < 2) setA(a + 1);
  }, [a]);

  React.useEffect(() => {
    console.log("EFFECT B");
    setB(a);
  }, [a]);

  return <h1>{a} {b}</h1>;
}
```

**Questions:**
- Total renders?
- Final UI?
- Exact effect sequence?

<details>
<summary>Answer</summary>

**Trace:**
```
RENDER (a=0, b=0)
EFFECT A → setA(1)
EFFECT B → setB(0)

RENDER (a=1, b=0)
EFFECT A → setA(2)
EFFECT B → setB(1)

RENDER (a=2, b=1)
EFFECT A → condition fails, no setA
EFFECT B → setB(2)

RENDER (a=2, b=2)
```

**Total renders:** 4

**Final UI:** `2 2`

**Key insight:** Each `a` change triggers both effects. EFFECT A stops at `a < 2`. EFFECT B always syncs `b` to `a`, so it trails by one render.

</details>

---

### Problem 8 — Object Identity Dependency Bug

```jsx
function App() {
  const [filters, setFilters] = React.useState({ category: "all" });

  React.useEffect(() => {
    console.log("FETCH");
  }, [filters]);

  return (
    <button onClick={() => setFilters({ category: "all" })}>Reset</button>
  );
}
```

**Why does clicking Reset still refetch? Senior fix?**

<details>
<summary>Answer</summary>

**Why:** Each click creates a new `{}` object. Even though `category: "all"` is the same value, `{ category: "all" } !== { category: "all" }`. React's dep comparison uses `Object.is`, which is reference equality for objects.

**Senior fixes:**
```jsx
// Fix 1: Depend on specific primitive fields
React.useEffect(() => {
  console.log("FETCH");
}, [filters.category]);

// Fix 2: Serialize (careful — order matters)
React.useEffect(() => {
  console.log("FETCH");
}, [JSON.stringify(filters)]);

// Fix 3: Use useReducer with stable actions
// Fix 4: Normalize to primitives at state level
const [category, setCategory] = React.useState("all");
```

</details>

---

### Problem 9 — Layout Effect vs Effect

```jsx
function App() {
  const [width, setWidth] = React.useState(0);
  const ref = React.useRef(null);

  React.useEffect(() => {
    setWidth(ref.current.offsetWidth);
  }, []);

  React.useLayoutEffect(() => {
    console.log("layoutEffect width:", ref.current.offsetWidth);
  }, []);

  return <div ref={ref} style={{ width: "50%" }}>Box: {width}px</div>;
}
```

**Questions:**
- What's the difference between useEffect and useLayoutEffect?
- Which one reads the correct DOM size?
- When would you see a flicker?

<details>
<summary>Answer</summary>

**Difference:**
- `useEffect` fires **after** browser paint (async, non-blocking)
- `useLayoutEffect` fires **synchronously after DOM mutations, before paint**

**Reading DOM measurements:** `useLayoutEffect` always reads the correct size because the DOM is committed but not yet painted. `useEffect` may read stale values if paint happened first (rare but possible with concurrent features).

**Flicker scenario:** Using `useEffect` to measure and then update state causes a double-paint — first paint shows `width=0`, then re-paints with correct value. Users see a flash. `useLayoutEffect` prevents this by updating before paint.

**Rule:** Use `useLayoutEffect` for DOM measurements + mutations. Use `useEffect` for everything else (data fetching, subscriptions).

</details>

---

### Problem 10 — Batching Behavior (React 18)

```jsx
function App() {
  const [a, setA] = React.useState(0);
  const [b, setB] = React.useState(0);
  console.log("RENDER", a, b);

  const handleClick = () => {
    setA(1);
    setB(1);
    setTimeout(() => {
      setA(2);
      setB(2);
    }, 0);
  };

  return <button onClick={handleClick}>Go</button>;
}
```

**Questions:**
- In React 17 vs React 18, how many renders does clicking cause?
- What changed?

<details>
<summary>Answer</summary>

**React 17:**
- `setA(1); setB(1)` → 1 render (batched inside event handler)
- `setTimeout` → 2 renders (NOT batched outside event handlers)
- **Total: 3 renders**

**React 18:**
- `setA(1); setB(1)` → 1 render (batched)
- `setTimeout setA(2); setB(2)` → 1 render (also batched — Automatic Batching)
- **Total: 2 renders**

**What changed:** React 18 introduced **Automatic Batching** — all state updates are batched everywhere (event handlers, setTimeout, promises, native events). Opt out with `ReactDOM.flushSync` if needed.

```jsx
import { flushSync } from 'react-dom';
flushSync(() => setA(1)); // forces immediate re-render
flushSync(() => setB(1)); // forces another
```

</details>

---

## Closure & Stale State

---

### Problem 11 — Async Stale Closure

```jsx
function App() {
  const [count, setCount] = React.useState(0);

  const handleClick = async () => {
    const snapshot = count;
    await new Promise(resolve => setTimeout(resolve, 2000));
    console.log("count now:", count);
    console.log("snapshot:", snapshot);
    setCount(count + 1);
  };

  return (
    <>
      <p>{count}</p>
      <button onClick={handleClick}>Async Add</button>
      <button onClick={() => setCount(c => c + 1)}>Sync Add</button>
    </>
  );
}
```

**Scenario:** Click "Async Add", then immediately click "Sync Add" 3 times. What's the final count and why?

<details>
<summary>Answer</summary>

**After 2 seconds:**
- `count` in closure is `0` (captured at click time)
- Sync clicks brought count to `3`
- `setCount(count + 1)` = `setCount(0 + 1)` = `1`

**Final count: 1** (not 4!)

**Why:** The async function closed over `count = 0`. When it resumes after the await, it reads its captured value, not the current state. Then `setCount(0 + 1)` overwrites the 3 sync updates.

**Fix — always use functional update in async:**
```jsx
setCount(c => c + 1); // reads current state at call time
```

</details>

---

### Problem 12 — Event Listener Stale Closure

```jsx
function App() {
  const [theme, setTheme] = React.useState("light");

  React.useEffect(() => {
    const handler = () => {
      console.log("current theme:", theme);
    };
    window.addEventListener("keydown", handler);
    return () => window.removeEventListener("keydown", handler);
  }, []); // intentional empty deps

  return (
    <button onClick={() => setTheme(t => t === "light" ? "dark" : "light")}>
      Toggle ({theme})
    </button>
  );
}
```

**Questions:**
- After toggling theme, what does pressing a key log?
- Fix with useRef?

<details>
<summary>Answer</summary>

**Always logs `"current theme: light"`** — the initial value.

**Why:** Event listener is registered once with `[]`. The `handler` closure captures `theme = "light"`. Toggling state creates new renders with new `theme` values, but the registered listener still holds the old closure.

**Fix with useRef:**
```jsx
const themeRef = React.useRef(theme);
themeRef.current = theme; // update every render

React.useEffect(() => {
  const handler = () => console.log("current theme:", themeRef.current);
  window.addEventListener("keydown", handler);
  return () => window.removeEventListener("keydown", handler);
}, []); // ref is always current, so [] is safe
```

</details>

---

### Problem 13 — Counter Race Condition

```jsx
function App() {
  const [count, setCount] = React.useState(0);

  const incrementThrice = () => {
    setCount(count + 1);
    setCount(count + 1);
    setCount(count + 1);
  };

  return (
    <>
      <h1>{count}</h1>
      <button onClick={incrementThrice}>+3</button>
    </>
  );
}
```

**What does the counter show after one click? Why?**

<details>
<summary>Answer</summary>

**Counter shows `1`**, not `3`.

**Why:** All three calls read the same `count` value from the closure (e.g., `0`). React batches them. It's like writing `count = 0 + 1` three times — the last one wins.

**Fix — functional update:**
```jsx
const incrementThrice = () => {
  setCount(c => c + 1);
  setCount(c => c + 1);
  setCount(c => c + 1);
};
```
Now each updater receives the result of the previous — React queues `0→1→2→3`. Counter shows `3`.

</details>

---

## Memoization & Performance

---

### Problem 14 — useCallback Trap

```jsx
const Child = React.memo(({ onSubmit }) => {
  console.log("CHILD RENDER");
  return <button onClick={onSubmit}>Submit</button>;
});

function App() {
  const [user, setUser] = React.useState({ name: "Alice" });

  const handleSubmit = React.useCallback(() => {
    console.log(user.name);
  }, [user]);

  return (
    <>
      <Child onSubmit={handleSubmit} />
      <button onClick={() => setUser({ name: "Alice" })}>Reset</button>
    </>
  );
}
```

**Does clicking Reset re-render Child? Why?**

<details>
<summary>Answer</summary>

**Yes, Child re-renders.**

**Why:** `user` dep in `useCallback` changes on every "Reset" click because `{ name: "Alice" }` creates a new object reference. New `user` → new `handleSubmit` reference → `React.memo` sees changed prop → Child re-renders.

**Fix:**
```jsx
// Option 1: Use useRef for the callback data
const userRef = React.useRef(user);
userRef.current = user;

const handleSubmit = React.useCallback(() => {
  console.log(userRef.current.name);
}, []); // no user dep needed

// Option 2: Depend on stable primitive
const [name, setName] = React.useState("Alice");
const handleSubmit = React.useCallback(() => {
  console.log(name);
}, [name]);
```

</details>

---

### Problem 15 — Premature useMemo

```jsx
function App() {
  const [items] = React.useState([1, 2, 3]);

  const doubled = React.useMemo(() => {
    return items.map(x => x * 2);
  }, [items]);

  return <ul>{doubled.map(d => <li key={d}>{d}</li>)}</ul>;
}
```

**Is this a good use of useMemo? What's the problem?**

<details>
<summary>Answer</summary>

**No — this is premature/useless memoization.**

**Problems:**
1. `items` is created with `useState([1,2,3])` — it never changes. The memo will never recompute.
2. Even if `items` did change, mapping 3 items is not expensive. useMemo has its own overhead (memory + comparison).
3. `items` is still a new array reference each render if defined inline: `useState([1,2,3])` — but useState preserves the reference across renders (unlike useMemo deps from props).

**When to use useMemo:**
- Genuinely expensive computations (heavy math, large data transforms, tree traversals)
- Stable reference needed as a dep for another hook
- Proven bottleneck via profiler

**Rule of thumb:** Don't memoize unless React DevTools Profiler shows it as a problem.

</details>

---

### Problem 16 — Context Re-render Trap

```jsx
const ThemeContext = React.createContext();

function App() {
  const [theme, setTheme] = React.useState("light");
  const [count, setCount] = React.useState(0);

  return (
    <ThemeContext.Provider value={{ theme, setTheme }}>
      <Child />
      <button onClick={() => setCount(c => c + 1)}>Count: {count}</button>
    </ThemeContext.Provider>
  );
}

const Child = React.memo(() => {
  const ctx = React.useContext(ThemeContext);
  console.log("CHILD RENDER");
  return <div>{ctx.theme}</div>;
});
```

**Does Child re-render when count changes? Why?**

<details>
<summary>Answer</summary>

**Yes, Child re-renders — despite React.memo.**

**Why:** Every time `count` changes, `App` re-renders. The `value={{ theme, setTheme }}` creates a **new object reference** on every render. Context consumers re-render whenever context value changes by reference. `React.memo` cannot help here because the re-render is triggered by context, not props.

**Fixes:**
```jsx
// Fix 1: Memoize the context value
const ctxValue = React.useMemo(
  () => ({ theme, setTheme }),
  [theme] // only changes when theme changes
);
<ThemeContext.Provider value={ctxValue}>

// Fix 2: Split contexts (theme vs setter)
const ThemeValueContext = React.createContext();
const ThemeSetterContext = React.createContext();
// setter never changes → consumers only subscribe to what they need
```

</details>

---

### Problem 17 — Virtualization Requirement

```jsx
function App() {
  const [items] = React.useState(Array.from({ length: 100000 }, (_, i) => i));

  return (
    <ul>
      {items.map(i => <li key={i}>Item {i}</li>)}
    </ul>
  );
}
```

**What's the problem and how do senior engineers solve it?**

<details>
<summary>Answer</summary>

**Problem:** Rendering 100,000 DOM nodes causes:
- Extremely slow initial paint (possibly 10+ seconds)
- Massive memory usage
- Janky scrolling

**Senior solutions:**

**1. Windowing/Virtualization (preferred):**
```jsx
import { FixedSizeList as List } from 'react-window';

function App() {
  const items = Array.from({ length: 100000 }, (_, i) => i);
  const Row = ({ index, style }) => (
    <div style={style}>Item {items[index]}</div>
  );
  return <List height={600} itemCount={items.length} itemSize={35}>{Row}</List>;
}
```
Only renders ~20 items at a time (the visible viewport). `react-window` or `react-virtual` (TanStack).

**2. Pagination** — load/show 50 at a time.

**3. Infinite scroll** — load more as user approaches bottom.

**4. Search/filter first** — never show all 100k, narrow dataset first.

</details>

---

## Redux & State Management

---

### Problem 18 — Redux Selector Re-render

```jsx
// store: { users: [...1000 users], ui: { loading: false } }

const UserList = () => {
  const users = useSelector(state => state.users);
  console.log("RENDER");
  return <div>{users.length} users</div>;
};
```

**When does UserList re-render? What's the bug?**

<details>
<summary>Answer</summary>

**Re-renders whenever ANY part of the store changes** — including `ui.loading`.

**Why:** `useSelector` re-renders when the selected value changes. `state.users` is the array reference. If a reducer returns a new root state object (even for unrelated slice changes), `state.users` reference might still be the same — but if ANY reducer does a spread (`...state`), references can cascade.

**Also:** If the selector derives new data:
```jsx
const activeUsers = useSelector(state => state.users.filter(u => u.active));
// .filter always returns new array → always different reference → always re-renders
```

**Fixes:**
```jsx
// Fix 1: Memoized selector with reselect
import { createSelector } from '@reduxjs/toolkit';
const selectActiveUsers = createSelector(
  state => state.users,
  users => users.filter(u => u.active)
);
const activeUsers = useSelector(selectActiveUsers);

// Fix 2: shallowEqual for object selectors
import { shallowEqual } from 'react-redux';
const { name, email } = useSelector(
  state => ({ name: state.user.name, email: state.user.email }),
  shallowEqual
);
```

</details>

---

### Problem 19 — Redux Thunk Race Condition

```jsx
// Action creator
const fetchUser = (id) => async (dispatch) => {
  dispatch({ type: "FETCH_START" });
  const user = await api.getUser(id);
  dispatch({ type: "FETCH_SUCCESS", payload: user });
};

// Component
function Profile({ userId }) {
  const dispatch = useDispatch();
  React.useEffect(() => {
    dispatch(fetchUser(userId));
  }, [userId]);
}
```

**Scenario:** User navigates from profile `1` to profile `2` quickly. What bug can occur?

<details>
<summary>Answer</summary>

**Race condition:** If user `1` request is slow and user `2` request is fast:
1. Fetch user `1` starts
2. `userId` changes to `2`
3. Fetch user `2` starts and completes → shows user 2 data ✓
4. Fetch user `1` completes → overwrites store with user 1 data ✗

**Fix — abort/ignore outdated requests:**
```jsx
const fetchUser = (id) => async (dispatch, getState) => {
  dispatch({ type: "FETCH_START" });
  const controller = new AbortController();
  try {
    const user = await api.getUser(id, { signal: controller.signal });
    dispatch({ type: "FETCH_SUCCESS", payload: user });
  } catch (e) {
    if (e.name !== "AbortError") dispatch({ type: "FETCH_ERROR" });
  }
  return () => controller.abort();
};

// Better: RTK Query handles this automatically
const { data } = useGetUserQuery(userId);
```

</details>

---

### Problem 20 — Mutating Redux State Directly

```jsx
// Reducer
function usersReducer(state = [], action) {
  switch (action.type) {
    case "ADD_USER":
      state.push(action.payload); // ← mutation
      return state;
    default:
      return state;
  }
}
```

**Why doesn't the UI update? How does Redux detect changes?**

<details>
<summary>Answer</summary>

**Why UI doesn't update:** Redux uses reference equality (`===`) to detect state changes. Mutating `state.push()` modifies the existing array in place — the reference is the same. `state === state` → Redux thinks nothing changed → no re-render.

**How Redux detects changes:** `useSelector` calls the selector and compares result with previous result using `===` (or `shallowEqual` if provided). Same reference = no update.

**Fix:**
```jsx
case "ADD_USER":
  return [...state, action.payload]; // new array reference

// RTK uses Immer — makes mutations safe:
const usersSlice = createSlice({
  name: "users",
  initialState: [],
  reducers: {
    addUser(state, action) {
      state.push(action.payload); // Immer tracks this and returns new state
    }
  }
});
```

</details>

---

### Problem 21 — Redux Normalization Problem

```jsx
// State shape (denormalized)
{
  posts: [
    { id: 1, title: "Post 1", author: { id: 10, name: "Alice" } },
    { id: 2, title: "Post 2", author: { id: 10, name: "Alice" } },
  ]
}
```

**If Alice changes her name, what happens? How do senior engineers structure this?**

<details>
<summary>Answer</summary>

**Problem:** You'd have to update Alice's name in every post that references her. Easy to miss, causes inconsistency.

**Normalized shape (senior approach):**
```js
{
  entities: {
    users: { 10: { id: 10, name: "Alice" } },
    posts: {
      1: { id: 1, title: "Post 1", authorId: 10 },
      2: { id: 2, title: "Post 2", authorId: 10 }
    }
  },
  ids: {
    posts: [1, 2]
  }
}
```

Update Alice once → both posts reflect the change via selector.

**RTK's createEntityAdapter does this automatically:**
```js
const usersAdapter = createEntityAdapter();
const usersSlice = createSlice({
  name: "users",
  initialState: usersAdapter.getInitialState(),
  reducers: {
    upsertUser: usersAdapter.upsertOne,
  }
});
```

</details>

---

### Problem 22 — Redux Middleware Ordering

```jsx
const store = configureStore({
  reducer: rootReducer,
  middleware: (getDefault) =>
    getDefault().concat(logger).prepend(crashReporter)
});
```

**What order do middlewares run in? Does order matter?**

<details>
<summary>Answer</summary>

**Order (action flows through):**
```
crashReporter → thunk → immutability → serializability → logger → reducer
```

`prepend` puts `crashReporter` first (before default middleware including `thunk`).
`concat` adds `logger` last.

**Yes, order critically matters:**
- `thunk` must run before `logger` — otherwise logger sees the thunk function, not the dispatched action
- `crashReporter` should be first — it needs to catch errors from all subsequent middleware
- `logger` should be last — it should log the final action form

**Pitfall:** If you put custom middleware after `logger`, logger won't see any actions dispatched by that middleware.

</details>

---

### Problem 23 — Zustand vs Redux Choice

A new feature needs:
- Global state for 3 components
- No server data
- Simple toggle + counter
- Team of 2 developers

**What would you choose and why?**

<details>
<summary>Answer</summary>

**Zustand** for this scenario.

**Why:**
```js
// Zustand — entire store in ~10 lines
import { create } from 'zustand';

const useStore = create(set => ({
  count: 0,
  darkMode: false,
  increment: () => set(s => ({ count: s.count + 1 })),
  toggleTheme: () => set(s => ({ darkMode: !s.darkMode }))
}));
```

vs Redux Toolkit setup (slice, store config, Provider, selectors, actions) — 40+ lines of boilerplate.

**Choose Redux when:**
- Complex async flows (RTK Query)
- DevTools + time-travel debugging needed
- Team > 5, shared conventions matter
- State shape is deeply nested or relational
- Server state caching is needed

**Choose Zustand when:**
- Small-to-medium client state
- Quick iteration
- Colocation of state and actions preferred
- No Provider wrapper needed

</details>

---

### Problem 24 — Redux DevTools Serialization Error

```jsx
const slice = createSlice({
  name: "uploads",
  initialState: { file: null },
  reducers: {
    setFile(state, action) {
      state.file = action.payload; // payload is a File object
    }
  }
});
```

**Why does Redux DevTools throw a warning? How to fix?**

<details>
<summary>Answer</summary>

**Warning:** `"A non-serializable value was detected in the state"` or in action.

**Why:** Redux DevTools (and RTK's serializable check middleware) requires all state/actions to be JSON-serializable. `File` objects contain methods, circular refs, and binary data — not serializable.

**Fixes:**
```js
// Fix 1: Store only serializable metadata
setFile(state, action) {
  const { name, size, type, lastModified } = action.payload;
  state.file = { name, size, type, lastModified };
  // Store actual File in a ref or module-level var
}

// Fix 2: Use useRef for the File object
const fileRef = React.useRef(null);
fileRef.current = selectedFile;
dispatch(setFileMeta({ name: selectedFile.name, size: selectedFile.size }));

// Fix 3: Disable check for specific action (not recommended)
middleware: (getDefault) => getDefault({
  serializableCheck: {
    ignoredActions: ['uploads/setFile'],
  }
})
```

</details>

---

## API Calls & Async Patterns

---

### Problem 25 — useEffect Fetch Without Cleanup

```jsx
function UserProfile({ userId }) {
  const [user, setUser] = React.useState(null);

  React.useEffect(() => {
    fetch(`/api/users/${userId}`)
      .then(res => res.json())
      .then(data => setUser(data));
  }, [userId]);

  return <div>{user?.name}</div>;
}
```

**What's wrong? How to fix?**

<details>
<summary>Answer</summary>

**Problems:**
1. **Memory leak + state update on unmounted component** — if component unmounts before fetch completes, `setUser` is called on dead component
2. **Race condition** — quick `userId` changes cause out-of-order updates
3. **No error handling**
4. **No loading state**

**Production-grade fix:**
```jsx
React.useEffect(() => {
  let cancelled = false;
  const controller = new AbortController();

  const fetchUser = async () => {
    try {
      const res = await fetch(`/api/users/${userId}`, {
        signal: controller.signal
      });
      if (!res.ok) throw new Error(res.statusText);
      const data = await res.json();
      if (!cancelled) setUser(data);
    } catch (err) {
      if (err.name !== "AbortError" && !cancelled) setError(err.message);
    }
  };

  fetchUser();
  return () => {
    cancelled = true;
    controller.abort();
  };
}, [userId]);
```

**Senior answer:** Use TanStack Query — it handles all of this automatically.

</details>

---

### Problem 26 — Loading State Machine

```jsx
function App() {
  const [loading, setLoading] = React.useState(false);
  const [error, setError] = React.useState(null);
  const [data, setData] = React.useState(null);

  const fetchData = async () => {
    setLoading(true);
    try {
      const res = await api.getData();
      setData(res);
      setError(null);
    } catch (e) {
      setError(e.message);
      setData(null);
    } finally {
      setLoading(false);
    }
  };
}
```

**What are the invalid states possible? How to prevent them?**

<details>
<summary>Answer</summary>

**Invalid states possible with 3 separate booleans:**
- `loading: true, error: "...", data: null` — shouldn't happen (error during load)
- `loading: false, error: "...", data: {...}` — contradictory
- `loading: true, data: {...}` — loading but already has data?

**2^3 = 8 combinations, only ~3 are valid.**

**Fix — use a state machine or discriminated union:**
```jsx
const [state, dispatch] = React.useReducer(
  (state, action) => {
    switch (action.type) {
      case "FETCH": return { status: "loading" };
      case "SUCCESS": return { status: "success", data: action.data };
      case "ERROR": return { status: "error", error: action.error };
    }
  },
  { status: "idle" }
);

// Usage
if (state.status === "loading") return <Spinner />;
if (state.status === "error") return <Error msg={state.error} />;
if (state.status === "success") return <Data items={state.data} />;
```

Only valid transitions are possible. This is the basis of XState.

</details>

---

### Problem 27 — Optimistic Update Pattern

```jsx
// Task: Implement a "like" button that feels instant but handles server failures
function Post({ post }) {
  const [liked, setLiked] = React.useState(post.liked);

  const handleLike = async () => {
    setLiked(true); // optimistic
    try {
      await api.likePost(post.id);
    } catch {
      setLiked(false); // rollback
    }
  };

  return <button onClick={handleLike}>{liked ? "♥" : "♡"}</button>;
}
```

**What's missing? How do senior engineers handle this in Redux/TanStack Query?**

<details>
<summary>Answer</summary>

**Missing from this implementation:**
- Preventing double-clicks during in-flight request
- Loading state during API call
- Showing the actual server state after success (likes count)
- Error message to user on rollback

**Complete implementation:**
```jsx
function Post({ post }) {
  const [optimisticLiked, setOptimisticLiked] = React.useState(post.liked);
  const [pending, setPending] = React.useState(false);

  const handleLike = async () => {
    if (pending) return;
    const prev = optimisticLiked;
    setOptimisticLiked(!prev);
    setPending(true);
    try {
      const result = await api.likePost(post.id);
      setOptimisticLiked(result.liked); // use server truth
    } catch {
      setOptimisticLiked(prev); // rollback
      toast.error("Failed to like post");
    } finally {
      setPending(false);
    }
  };
}
```

**TanStack Query approach:**
```jsx
const mutation = useMutation({
  mutationFn: (id) => api.likePost(id),
  onMutate: async (id) => {
    await queryClient.cancelQueries({ queryKey: ["post", id] });
    const previous = queryClient.getQueryData(["post", id]);
    queryClient.setQueryData(["post", id], old => ({ ...old, liked: !old.liked }));
    return { previous };
  },
  onError: (err, id, context) => {
    queryClient.setQueryData(["post", id], context.previous);
  },
  onSettled: (id) => {
    queryClient.invalidateQueries({ queryKey: ["post", id] });
  }
});
```

</details>

---

### Problem 28 — Request Deduplication

```jsx
// Three components all mounted simultaneously:
function ComponentA() {
  React.useEffect(() => { fetch("/api/user"); }, []);
}
function ComponentB() {
  React.useEffect(() => { fetch("/api/user"); }, []);
}
function ComponentC() {
  React.useEffect(() => { fetch("/api/user"); }, []);
}
```

**What problem exists? How do you solve it architecturally?**

<details>
<summary>Answer</summary>

**Problem:** 3 identical network requests fire simultaneously, wasting bandwidth, server resources, and possibly returning stale data if server state changes between calls.

**Solutions:**

**1. Lift state up** — fetch once in parent, pass as props
```jsx
function Parent() {
  const [user, setUser] = React.useState(null);
  React.useEffect(() => { api.getUser().then(setUser); }, []);
  return <>{user && <A user={user} />}<B user={user} /><C user={user} /></>;
}
```

**2. Context** — fetch once in context provider

**3. TanStack Query (best):**
```jsx
// All three components call this — only ONE request fires
const { data: user } = useQuery({ queryKey: ["user"], queryFn: api.getUser });
```
TanStack Query automatically deduplicates in-flight requests with the same key. Results are cached and shared.

**4. SWR** — same deduplication behavior

**5. Redux + thunk with in-flight tracking:**
```js
if (state.users.status === "loading") return; // skip if already fetching
```

</details>

---

### Problem 29 — Polling with Visibility

```jsx
function LiveScore({ gameId }) {
  const [score, setScore] = React.useState(null);

  React.useEffect(() => {
    const id = setInterval(async () => {
      const data = await api.getScore(gameId);
      setScore(data);
    }, 5000);
    return () => clearInterval(id);
  }, [gameId]);

  return <div>{score}</div>;
}
```

**What's the UX problem? How do you improve this?**

<details>
<summary>Answer</summary>

**Problems:**
1. Polls even when tab is hidden (wastes bandwidth)
2. Polls even when user navigates away briefly
3. No exponential backoff on failures
4. First data only appears after 5 seconds

**Production implementation:**
```jsx
React.useEffect(() => {
  let id;
  let active = true;

  const poll = async () => {
    if (!active || document.hidden) return;
    try {
      const data = await api.getScore(gameId);
      if (active) setScore(data);
    } catch {}
    if (active) id = setTimeout(poll, 5000);
  };

  const handleVisibility = () => {
    if (!document.hidden) poll(); // resume immediately on tab focus
  };

  poll(); // fetch immediately
  document.addEventListener("visibilitychange", handleVisibility);

  return () => {
    active = false;
    clearTimeout(id);
    document.removeEventListener("visibilitychange", handleVisibility);
  };
}, [gameId]);
```

**TanStack Query:**
```jsx
const { data } = useQuery({
  queryKey: ["score", gameId],
  queryFn: () => api.getScore(gameId),
  refetchInterval: 5000,
  refetchIntervalInBackground: false, // pauses when tab hidden
});
```

</details>

---

### Problem 30 — Dependent Queries

```jsx
function Dashboard({ userId }) {
  const [user, setUser] = React.useState(null);
  const [orders, setOrders] = React.useState([]);

  React.useEffect(() => {
    api.getUser(userId).then(setUser);
  }, [userId]);

  React.useEffect(() => {
    if (user) {
      api.getOrders(user.accountId).then(setOrders);
    }
  }, [user]);
}
```

**What's the problem with this pattern? Clean solution?**

<details>
<summary>Answer</summary>

**Problems:**
- Sequential waterfall: user fetch must complete before orders fetch starts
- Two useEffects, complex dep tracking
- No error boundaries between them
- Loading states are hard to coordinate

**Clean solution with TanStack Query:**
```jsx
function Dashboard({ userId }) {
  const { data: user } = useQuery({
    queryKey: ["user", userId],
    queryFn: () => api.getUser(userId),
  });

  const { data: orders } = useQuery({
    queryKey: ["orders", user?.accountId],
    queryFn: () => api.getOrders(user.accountId),
    enabled: !!user?.accountId, // ← waits for user
  });
}
```

**`enabled` flag** — query only fires when condition is true. Automatically retries when `user` becomes available. Handles caching, deduplication, loading states.

**Parallel when possible:**
```jsx
const results = useQueries({
  queries: [
    { queryKey: ["user", userId], queryFn: () => api.getUser(userId) },
    { queryKey: ["settings"], queryFn: api.getSettings },
  ]
});
```

</details>

---

### Problem 31 — Infinite Scroll Implementation

```jsx
function Feed() {
  const [posts, setPosts] = React.useState([]);
  const [page, setPage] = React.useState(1);

  React.useEffect(() => {
    api.getPosts(page).then(data => {
      setPosts(prev => [...prev, ...data]); // append
    });
  }, [page]);

  const loadMore = () => setPage(p => p + 1);

  return (
    <>
      {posts.map(p => <Post key={p.id} post={p} />)}
      <button onClick={loadMore}>Load More</button>
    </>
  );
}
```

**Problems and senior implementation?**

<details>
<summary>Answer</summary>

**Problems:**
- No loading/error state
- `[...prev, ...data]` grows unboundedly (memory leak for long sessions)
- Button-based load more instead of auto-scroll trigger
- Re-fetching page 1 if component remounts

**Senior implementation with IntersectionObserver:**
```jsx
function Feed() {
  const sentinelRef = React.useRef(null);

  const { data, fetchNextPage, hasNextPage, isFetchingNextPage } =
    useInfiniteQuery({
      queryKey: ["posts"],
      queryFn: ({ pageParam = 1 }) => api.getPosts(pageParam),
      getNextPageParam: (lastPage) => lastPage.nextPage ?? undefined,
    });

  React.useEffect(() => {
    const observer = new IntersectionObserver(
      ([entry]) => { if (entry.isIntersecting && hasNextPage) fetchNextPage(); },
      { threshold: 0.1 }
    );
    if (sentinelRef.current) observer.observe(sentinelRef.current);
    return () => observer.disconnect();
  }, [hasNextPage, fetchNextPage]);

  return (
    <>
      {data?.pages.flatMap(page => page.posts).map(p => (
        <Post key={p.id} post={p} />
      ))}
      <div ref={sentinelRef}>
        {isFetchingNextPage && <Spinner />}
      </div>
    </>
  );
}
```

</details>

---

### Problem 32 — Debounced Search

```jsx
function Search() {
  const [query, setQuery] = React.useState("");
  const [results, setResults] = React.useState([]);

  React.useEffect(() => {
    if (query) {
      api.search(query).then(setResults);
    }
  }, [query]);

  return <input value={query} onChange={e => setQuery(e.target.value)} />;
}
```

**What's wrong? Implement proper debounced search.**

<details>
<summary>Answer</summary>

**Problems:**
- Fires API call on EVERY keystroke (extremely chatty)
- No cleanup → race conditions on fast typing
- "abc" typed = 3 API calls: "a", "ab", "abc"

**Debounced with cleanup:**
```jsx
function Search() {
  const [query, setQuery] = React.useState("");
  const [results, setResults] = React.useState([]);

  React.useEffect(() => {
    if (!query.trim()) return setResults([]);

    const timer = setTimeout(async () => {
      const controller = new AbortController();
      try {
        const data = await api.search(query, { signal: controller.signal });
        setResults(data);
      } catch (e) {
        if (e.name !== "AbortError") console.error(e);
      }
    }, 300);

    return () => clearTimeout(timer);
  }, [query]);
}
```

**Custom hook:**
```jsx
function useDebounce(value, delay) {
  const [debounced, setDebounced] = React.useState(value);
  React.useEffect(() => {
    const id = setTimeout(() => setDebounced(value), delay);
    return () => clearTimeout(id);
  }, [value, delay]);
  return debounced;
}

// Usage
const debouncedQuery = useDebounce(query, 300);
React.useEffect(() => { if (debouncedQuery) api.search(debouncedQuery).then(setResults); }, [debouncedQuery]);
```

</details>

---

## Advanced Hooks

---

### Problem 33 — Custom Hook Rules Violation

```jsx
function App({ isLoggedIn }) {
  if (isLoggedIn) {
    const [user, setUser] = React.useState(null); // ← conditional hook
    React.useEffect(() => {
      api.getUser().then(setUser);
    }, []);
  }

  return <div>App</div>;
}
```

**Why does React throw? What's the fix?**

<details>
<summary>Answer</summary>

**Error:** `"React Hook 'useState' is called conditionally. React Hooks must be called in the same order in every component render."`

**Why:** React tracks hooks by call order in a linked list. If `isLoggedIn` changes from `true` to `false`, hook call #1 disappears, and React loses track of which state/effect belongs to which hook call. The entire hook state becomes corrupted.

**Fix 1 — Always call hooks, conditionally use the result:**
```jsx
function App({ isLoggedIn }) {
  const [user, setUser] = React.useState(null);

  React.useEffect(() => {
    if (!isLoggedIn) return;
    api.getUser().then(setUser);
  }, [isLoggedIn]);

  return <div>{isLoggedIn ? user?.name : "Guest"}</div>;
}
```

**Fix 2 — Split into components:**
```jsx
function AuthenticatedApp() {
  const [user, setUser] = React.useState(null);
  // all hooks here
}
function App({ isLoggedIn }) {
  return isLoggedIn ? <AuthenticatedApp /> : <div>Guest</div>;
}
```

</details>

---

### Problem 34 — useReducer vs useState

```jsx
// Current code with 5 related states
const [loading, setLoading] = React.useState(false);
const [data, setData] = React.useState(null);
const [error, setError] = React.useState(null);
const [page, setPage] = React.useState(1);
const [totalPages, setTotalPages] = React.useState(0);
```

**When should you switch to useReducer? Rewrite this.**

<details>
<summary>Answer</summary>

**Switch to useReducer when:**
- Multiple related state updates happen together
- Next state depends on previous state in complex ways
- State transitions need to be explicit and testable
- More than 2-3 related useState calls

**Rewrite:**
```jsx
const initialState = {
  status: "idle", // idle | loading | success | error
  data: null,
  error: null,
  page: 1,
  totalPages: 0,
};

function fetchReducer(state, action) {
  switch (action.type) {
    case "FETCH_START":
      return { ...state, status: "loading", error: null };
    case "FETCH_SUCCESS":
      return {
        ...state,
        status: "success",
        data: action.data,
        totalPages: action.totalPages,
      };
    case "FETCH_ERROR":
      return { ...state, status: "error", error: action.error };
    case "SET_PAGE":
      return { ...state, page: action.page };
    default:
      return state;
  }
}

const [state, dispatch] = React.useReducer(fetchReducer, initialState);
```

Now state transitions are atomic — no intermediate inconsistent states.

</details>

---

### Problem 35 — useImperativeHandle Usage

```jsx
// Parent wants to call focus() on a custom Input component
function Parent() {
  const inputRef = React.useRef(null);
  return (
    <>
      <FancyInput ref={inputRef} />
      <button onClick={() => inputRef.current.focus()}>Focus</button>
    </>
  );
}

const FancyInput = ({ ref }) => { // ← this won't work
  return <input />;
};
```

**What's wrong? How do you expose imperative methods from a child?**

<details>
<summary>Answer</summary>

**Problems:**
1. Regular function components don't accept `ref` as a prop — it's special
2. Forwarding `ref` requires `React.forwardRef`
3. Exposing custom methods requires `useImperativeHandle`

**Fix:**
```jsx
const FancyInput = React.forwardRef((props, ref) => {
  const inputRef = React.useRef(null);

  React.useImperativeHandle(ref, () => ({
    focus: () => inputRef.current.focus(),
    clear: () => { inputRef.current.value = ""; },
    getValue: () => inputRef.current.value,
  }), []);

  return <input ref={inputRef} {...props} />;
});

// Parent
const inputRef = React.useRef(null);
inputRef.current.focus(); // works
inputRef.current.clear(); // works
inputRef.current.value;   // undefined — not exposed!
```

**Note:** In React 19, `ref` is passed as a regular prop — `forwardRef` is no longer needed.

</details>

---

### Problem 36 — useTransition for Non-urgent Updates

```jsx
function App() {
  const [query, setQuery] = React.useState("");
  const [list, setList] = React.useState(largeList); // 10,000 items

  const handleChange = (e) => {
    setQuery(e.target.value);
    const filtered = largeList.filter(item =>
      item.name.includes(e.target.value)
    );
    setList(filtered); // slow, blocks typing
  };

  return (
    <>
      <input value={query} onChange={handleChange} />
      {list.map(item => <Item key={item.id} item={item} />)}
    </>
  );
}
```

**Why does typing feel laggy? Fix with useTransition.**

<details>
<summary>Answer</summary>

**Why laggy:** Both state updates (input + list filter) are treated with equal priority. Filtering 10k items blocks the main thread, making the input feel unresponsive.

**Fix with useTransition:**
```jsx
function App() {
  const [query, setQuery] = React.useState("");
  const [list, setList] = React.useState(largeList);
  const [isPending, startTransition] = React.useTransition();

  const handleChange = (e) => {
    const value = e.target.value;
    setQuery(value); // urgent — renders immediately

    startTransition(() => {
      // non-urgent — can be interrupted/deferred
      const filtered = largeList.filter(item => item.name.includes(value));
      setList(filtered);
    });
  };

  return (
    <>
      <input value={query} onChange={handleChange} />
      {isPending && <Spinner />}
      {list.map(item => <Item key={item.id} item={item} />)}
    </>
  );
}
```

`startTransition` marks updates as interruptible. React will prioritize the input update (stay responsive) and defer the list update. If the user types again before the list renders, the old transition is abandoned.

</details>

---

### Problem 37 — useDeferredValue

```jsx
// Similar to Problem 36 but you don't control where the slow update happens
function App() {
  const [query, setQuery] = React.useState("");
  return (
    <>
      <input value={query} onChange={e => setQuery(e.target.value)} />
      <SlowList query={query} /> {/* can't modify this component */}
    </>
  );
}
```

**How does useDeferredValue help here?**

<details>
<summary>Answer</summary>

**useDeferredValue** — defer a value's update without wrapping setState:

```jsx
function App() {
  const [query, setQuery] = React.useState("");
  const deferredQuery = React.useDeferredValue(query);
  const isStale = query !== deferredQuery;

  return (
    <>
      <input value={query} onChange={e => setQuery(e.target.value)} />
      <div style={{ opacity: isStale ? 0.5 : 1 }}>
        <SlowList query={deferredQuery} />
      </div>
    </>
  );
}
```

- Input responds immediately with `query`
- `SlowList` receives `deferredQuery` (may be one render behind)
- `isStale` lets you show loading indicator
- React may render with the old deferred value while computing the new one

**vs useTransition:**
- `useTransition` — you control which `setState` is non-urgent
- `useDeferredValue` — you defer a value from props or state you don't control

</details>

---

## Context & Composition

---

### Problem 38 — God Context Anti-pattern

```jsx
const AppContext = React.createContext();

function AppProvider({ children }) {
  const [user, setUser] = React.useState(null);
  const [theme, setTheme] = React.useState("light");
  const [cart, setCart] = React.useState([]);
  const [notifications, setNotifications] = React.useState([]);
  const [language, setLanguage] = React.useState("en");

  return (
    <AppContext.Provider value={{ user, setUser, theme, setTheme, cart, setCart, notifications, setNotifications, language, setLanguage }}>
      {children}
    </AppContext.Provider>
  );
}
```

**What's the problem? How to split this correctly?**

<details>
<summary>Answer</summary>

**Problem:** Any component consuming `AppContext` re-renders when ANY of these values change. A theme change re-renders cart components. A notification re-renders user profile.

**Fix — split by change frequency and concern:**
```jsx
// Stable (rare changes) — theme, language
const PreferencesContext = React.createContext();
function PreferencesProvider({ children }) {
  const [theme, setTheme] = React.useState("light");
  const [language, setLanguage] = React.useState("en");
  const value = React.useMemo(() => ({ theme, setTheme, language, setLanguage }), [theme, language]);
  return <PreferencesContext.Provider value={value}>{children}</PreferencesContext.Provider>;
}

// User (changes on login/logout)
const UserContext = React.createContext();

// Volatile (frequent changes) — cart, notifications
const CartContext = React.createContext();
const NotificationsContext = React.createContext();

// Compose
function AppProvider({ children }) {
  return (
    <PreferencesProvider>
      <UserProvider>
        <CartProvider>
          <NotificationsProvider>{children}</NotificationsProvider>
        </CartProvider>
      </UserProvider>
    </PreferencesProvider>
  );
}
```

Components only subscribe to the context they need → fewer re-renders.

</details>

---

### Problem 39 — Compound Component Pattern

```jsx
// Bad — too many props ("prop drilling to itself")
<Modal
  isOpen={open}
  title="Confirm Delete"
  body="Are you sure?"
  onConfirm={handleDelete}
  onCancel={() => setOpen(false)}
  confirmText="Delete"
  cancelText="Cancel"
  confirmVariant="danger"
  icon="warning"
/>
```

**Implement this as a compound component.**

<details>
<summary>Answer</summary>

```jsx
const ModalContext = React.createContext();

function Modal({ children, isOpen }) {
  if (!isOpen) return null;
  return (
    <ModalContext.Provider value={{}}>
      <div className="modal-overlay">
        <div className="modal">{children}</div>
      </div>
    </ModalContext.Provider>
  );
}

Modal.Header = function ModalHeader({ children }) {
  return <div className="modal-header">{children}</div>;
};

Modal.Body = function ModalBody({ children }) {
  return <div className="modal-body">{children}</div>;
};

Modal.Footer = function ModalFooter({ children }) {
  return <div className="modal-footer">{children}</div>;
};

// Usage — fully composable
<Modal isOpen={open}>
  <Modal.Header>
    <WarningIcon /> Confirm Delete
  </Modal.Header>
  <Modal.Body>Are you sure you want to delete this item?</Modal.Body>
  <Modal.Footer>
    <Button variant="danger" onClick={handleDelete}>Delete</Button>
    <Button onClick={() => setOpen(false)}>Cancel</Button>
  </Modal.Footer>
</Modal>
```

**Benefits:** Callers control composition. No prop explosion. Each sub-component is independently styled/extended.

</details>

---

### Problem 40 — Render Props vs Hooks

```jsx
// Old render props pattern
<MouseTracker render={({ x, y }) => (
  <div>Mouse at {x}, {y}</div>
)} />

// Modern equivalent?
```

**Convert to a custom hook. When would you still use render props?**

<details>
<summary>Answer</summary>

**Custom hook (preferred):**
```jsx
function useMousePosition() {
  const [position, setPosition] = React.useState({ x: 0, y: 0 });

  React.useEffect(() => {
    const handler = (e) => setPosition({ x: e.clientX, y: e.clientY });
    window.addEventListener("mousemove", handler);
    return () => window.removeEventListener("mousemove", handler);
  }, []);

  return position;
}

// Usage — clean and composable
function App() {
  const { x, y } = useMousePosition();
  return <div>Mouse at {x}, {y}</div>;
}
```

**When to still use render props:**
- When the rendered output needs the logic but the parent controls layout (e.g., `<DataTable renderRow={...} />`)
- Libraries that can't assume rendering environment (React Native compat)
- `children as function` for inversion of control (the parent controls what gets rendered)

```jsx
// Still valid render prop use case
<List
  items={items}
  renderItem={(item) => <CustomCard key={item.id} item={item} />}
/>
```

</details>

---

## Architecture & Patterns

---

### Problem 41 — Component Too Large

```jsx
// 400-line component with: fetch logic, form validation,
// error handling, UI rendering, analytics, auth checks
function UserRegistrationPage() {
  // 30 useState calls
  // 10 useEffect calls
  // 5 complex event handlers
  // 200 lines of JSX
}
```

**How do you refactor this? What's your strategy?**

<details>
<summary>Answer</summary>

**Strategy — Separation of Concerns:**

**1. Extract custom hooks (logic):**
```jsx
// useRegistrationForm.js
function useRegistrationForm() {
  const [values, setValues] = React.useState(initialValues);
  const [errors, setErrors] = React.useState({});
  const validate = () => { /* ... */ };
  const handleSubmit = async () => { /* ... */ };
  return { values, errors, handleSubmit, setValues };
}

// useRegistrationAnalytics.js
function useRegistrationAnalytics() {
  const trackStep = (step) => analytics.track("registration_step", { step });
  return { trackStep };
}
```

**2. Extract sub-components (UI):**
```jsx
// RegistrationForm.jsx
// PersonalInfoStep.jsx
// PasswordStep.jsx
// SuccessScreen.jsx
```

**3. Extract utilities:**
```jsx
// validators.js — pure functions, easily testable
export const validateEmail = (email) => /.../.test(email);
```

**Result:**
```jsx
function UserRegistrationPage() {
  const form = useRegistrationForm();
  const { trackStep } = useRegistrationAnalytics();
  const { user } = useAuth();

  return (
    <PageLayout>
      <RegistrationForm {...form} onStepChange={trackStep} />
    </PageLayout>
  );
}
```

50 lines, clear responsibilities, each piece independently testable.

</details>

---

### Problem 42 — Prop Drilling Solution

```jsx
// Theme needed 5 levels deep
<App>        // theme state lives here
  <Layout>   // passes theme down
    <Page>   // passes theme down
      <Section>  // passes theme down
        <Card theme={theme} />  // finally uses it
```

**Three ways to solve prop drilling — tradeoffs?**

<details>
<summary>Answer</summary>

**1. Context API:**
```jsx
const ThemeContext = React.createContext("light");
// App wraps with Provider, Card calls useContext
// ✓ Clean, built-in, good for truly global state
// ✗ Re-renders all consumers on change
```

**2. Component Composition (underused):**
```jsx
function App() {
  const [theme, setTheme] = React.useState("light");
  return (
    <Layout>
      <Page>
        <Section>
          <Card theme={theme} /> {/* Card is passed as children, not recreated */}
        </Section>
      </Page>
    </Layout>
  );
}
// ✓ No extra abstraction needed
// ✓ Layout/Page/Section don't know about theme
// ✗ Less flexible for deeply dynamic trees
```

**3. State manager (Zustand/Redux):**
```jsx
const useTheme = () => useStore(s => s.theme);
// Card reads directly from store
// ✓ No prop threading at all
// ✗ Adds external dependency for simple cases
```

**Rule:** Composition first → Context for global stable data → Zustand/Redux for complex shared state.

</details>

---

### Problem 43 — Code Splitting & Lazy Loading

```jsx
import HeavyChart from "./HeavyChart"; // 200kb bundle

function Dashboard() {
  const [showChart, setShowChart] = React.useState(false);
  return (
    <>
      <button onClick={() => setShowChart(true)}>Show Chart</button>
      {showChart && <HeavyChart />}
    </>
  );
}
```

**HeavyChart is always bundled even if never shown. Fix this.**

<details>
<summary>Answer</summary>

**Lazy loading with Suspense:**
```jsx
const HeavyChart = React.lazy(() => import("./HeavyChart"));

function Dashboard() {
  const [showChart, setShowChart] = React.useState(false);
  return (
    <>
      <button onClick={() => setShowChart(true)}>Show Chart</button>
      <React.Suspense fallback={<div>Loading chart...</div>}>
        {showChart && <HeavyChart />}
      </React.Suspense>
    </>
  );
}
```

**Preloading on hover (better UX):**
```jsx
const chartPromise = React.lazy(() => import("./HeavyChart"));

<button
  onMouseEnter={() => import("./HeavyChart")} // preload
  onClick={() => setShowChart(true)}
>
  Show Chart
</button>
```

**Route-based splitting (most common):**
```jsx
const AdminPage = React.lazy(() => import("./pages/AdminPage"));
const UserPage = React.lazy(() => import("./pages/UserPage"));
```

Each route chunk loads only when navigated to.

</details>

---

### Problem 44 — Error Boundary Implementation

```jsx
function App() {
  return (
    <div>
      <UserProfile userId={null} /> {/* will throw */}
    </div>
  );
}
```

**How do error boundaries work? Implement one with recovery.**

<details>
<summary>Answer</summary>

**Error boundaries must be class components** (no hook equivalent yet):

```jsx
class ErrorBoundary extends React.Component {
  constructor(props) {
    super(props);
    this.state = { hasError: false, error: null };
  }

  static getDerivedStateFromError(error) {
    return { hasError: true, error };
  }

  componentDidCatch(error, info) {
    // Log to error tracking service
    errorTracker.log(error, info.componentStack);
  }

  render() {
    if (this.state.hasError) {
      return this.props.fallback || (
        <div>
          <h2>Something went wrong</h2>
          <button onClick={() => this.setState({ hasError: false, error: null })}>
            Try Again
          </button>
        </div>
      );
    }
    return this.props.children;
  }
}

// Usage
<ErrorBoundary fallback={<UserProfileError />}>
  <UserProfile userId={null} />
</ErrorBoundary>
```

**react-error-boundary library:**
```jsx
import { ErrorBoundary, useErrorBoundary } from 'react-error-boundary';

<ErrorBoundary
  FallbackComponent={ErrorFallback}
  onError={(error, info) => logger.log(error)}
  onReset={() => queryClient.clear()}
>
  <UserProfile />
</ErrorBoundary>
```

**Note:** Error boundaries do NOT catch: event handlers, async code, SSR errors, errors inside the boundary itself.

</details>

---

### Problem 45 — Portal Usage

```jsx
function Modal({ children }) {
  return (
    <div className="modal-overlay">
      {children}
    </div>
  );
}

// Problem: Modal inside an overflow:hidden parent clips the overlay
```

**When and how do you use React Portals?**

<details>
<summary>Answer</summary>

**When:** When a component needs to visually break out of its parent's CSS constraints (overflow:hidden, z-index stacking context, transform).

Common cases: modals, tooltips, dropdowns, toasts.

```jsx
import { createPortal } from 'react-dom';

function Modal({ children, isOpen }) {
  if (!isOpen) return null;

  return createPortal(
    <div
      className="modal-overlay"
      onClick={(e) => e.target === e.currentTarget && onClose()}
    >
      <div className="modal-content">
        {children}
      </div>
    </div>,
    document.body // renders directly in body, outside React tree's DOM location
  );
}
```

**Key points:**
- Portal renders into a different DOM node but stays in React component tree
- Events bubble through React tree (not DOM tree) — `onClick` on parent still works
- Context works across portals (same React tree)
- Use `useEffect` cleanup to remove portal on unmount

</details>

---

### Problem 46 — HOC vs Custom Hook

```jsx
// Higher Order Component (old pattern)
const withAuth = (WrappedComponent) => {
  return function AuthWrapper(props) {
    const { user } = useAuth();
    if (!user) return <Redirect to="/login" />;
    return <WrappedComponent {...props} user={user} />;
  };
};

export default withAuth(Dashboard);
```

**When would you use HOCs in 2025? When prefer hooks?**

<details>
<summary>Answer</summary>

**Prefer hooks (90% of cases):**
```jsx
function Dashboard() {
  const { user, isLoading } = useAuth();
  if (isLoading) return <Spinner />;
  if (!user) return <Navigate to="/login" />;
  return <DashboardContent user={user} />;
}
```
- No wrapper hell in DevTools
- Explicit — you can see the auth check in the component
- TypeScript inference works better

**Still use HOCs when:**
- Class components (can't use hooks)
- Cross-cutting concerns that modify rendering behavior (e.g., `React.memo`, `React.forwardRef` — these ARE HOCs)
- Third-party library HOC patterns you must integrate
- When you want to intercept/wrap rendering behavior without modifying the component:

```jsx
const withErrorBoundary = (Component) => (props) => (
  <ErrorBoundary>
    <Component {...props} />
  </ErrorBoundary>
);
```

</details>

---

### Problem 47 — Suspense Data Fetching

```jsx
// Old way
function UserProfile({ userId }) {
  const [user, setUser] = React.useState(null);
  const [loading, setLoading] = React.useState(true);

  React.useEffect(() => {
    api.getUser(userId).then(u => {
      setUser(u);
      setLoading(false);
    });
  }, [userId]);

  if (loading) return <Spinner />;
  return <div>{user.name}</div>;
}
```

**How does Suspense-compatible data fetching change this?**

<details>
<summary>Answer</summary>

**Suspense-compatible approach:**

The component "suspends" (throws a Promise) when data isn't ready. React catches it, shows the fallback, and retries when the Promise resolves.

```jsx
// With TanStack Query (Suspense mode)
function UserProfile({ userId }) {
  const { data: user } = useSuspenseQuery({
    queryKey: ["user", userId],
    queryFn: () => api.getUser(userId),
  });

  // No loading check needed — component only renders when data is ready
  return <div>{user.name}</div>;
}

// Parent handles loading
function App() {
  return (
    <React.Suspense fallback={<Spinner />}>
      <UserProfile userId={1} />
    </React.Suspense>
  );
}
```

**Benefits:**
- No `if (loading) return` in component
- Parallel data loading with `Promise.all`-like behavior
- Loading state is a UI concern, not a data concern
- Works with `useTransition` for non-blocking navigation

</details>

---

### Problem 48 — Reconciliation & Key Prop

```jsx
function App() {
  const [items, setItems] = React.useState(["A", "B", "C"]);

  const removeFirst = () => setItems(items.slice(1));

  return (
    <ul>
      {items.map((item, index) => (
        <li key={index}>
          <input defaultValue={item} />
        </li>
      ))}
    </ul>
  );
}
```

**Scenario:** Type into all three inputs. Click "Remove First". What happens? Why is it wrong?**

<details>
<summary>Answer</summary>

**What happens:** The input values shift! If you typed "AA", "BB", "CC", after removing first you see "AA", "BB" (not "BB", "CC").

**Why:** `key={index}` means React maps DOM nodes by position, not identity. Removing item at index 0:
- Old: key=0:"A", key=1:"B", key=2:"C"
- New: key=0:"B", key=1:"C"

React reuses the existing DOM node at key=0 (which has the user's typed "AA") and just changes the `defaultValue` prop. But `defaultValue` is uncontrolled — it only sets the initial value, not the current value. So the input retains "AA".

**Fix — use stable unique IDs:**
```jsx
const [items, setItems] = React.useState([
  { id: "a1", label: "A" },
  { id: "b2", label: "B" },
  { id: "c3", label: "C" },
]);

{items.map(item => (
  <li key={item.id}> {/* stable ID, not index */}
    <input defaultValue={item.label} />
  </li>
))}
```

Now React correctly destroys/creates DOM nodes when items are removed.

</details>

---

### Problem 49 — Controlled vs Uncontrolled

```jsx
function Form() {
  return (
    <>
      {/* Controlled */}
      <input value={name} onChange={e => setName(e.target.value)} />

      {/* Uncontrolled */}
      <input defaultValue="Alice" ref={inputRef} />
    </>
  );
}
```

**When do you choose uncontrolled? What's wrong with mixing?**

<details>
<summary>Answer</summary>

**Controlled:** React owns the value. Every keystroke updates state → triggers re-render → input reflects state.

**Uncontrolled:** DOM owns the value. Read with `ref.current.value` only when needed (e.g., on submit).

**Use uncontrolled for:**
- File inputs (`<input type="file">` — always uncontrolled)
- Integrating with non-React code
- Performance-critical forms with many fields (no re-render on every keystroke)
- Simple forms where you only need value on submit

**The mixing bug:**
```jsx
// ❌ WRONG — switching from uncontrolled to controlled
const [value, setValue] = React.useState(undefined); // undefined = uncontrolled
<input value={value} onChange={e => setValue(e.target.value)} />
// When value becomes a string → React warns: "component is changing
// an uncontrolled input to be controlled"
```

**Fix:** Always initialize with a string (controlled) or use `defaultValue` (uncontrolled). Never switch.

```jsx
const [value, setValue] = React.useState(""); // always controlled
```

</details>

---

### Problem 50 — Form Library vs Custom Form

**When do you reach for React Hook Form / Formik vs building custom?**

<details>
<summary>Answer</summary>

**Build custom when:**
- 1-3 fields, simple validation
- No reuse across the app
- Full control over UX needed

**Use React Hook Form when:**
- Complex validation rules
- Many fields (performance matters — RHF is uncontrolled internally)
- Integration with schema validation (Zod, Yup)
- Reusable form patterns across app

```jsx
// React Hook Form + Zod
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { z } from "zod";

const schema = z.object({
  email: z.string().email("Invalid email"),
  password: z.string().min(8, "Min 8 characters"),
});

function LoginForm() {
  const { register, handleSubmit, formState: { errors } } = useForm({
    resolver: zodResolver(schema),
    defaultValues: { email: "", password: "" },
  });

  const onSubmit = (data) => api.login(data);

  return (
    <form onSubmit={handleSubmit(onSubmit)}>
      <input {...register("email")} />
      {errors.email && <p>{errors.email.message}</p>}

      <input type="password" {...register("password")} />
      {errors.password && <p>{errors.password.message}</p>}

      <button type="submit">Login</button>
    </form>
  );
}
```

**Benefits:** No re-render on every keystroke, schema-driven validation, first-class TypeScript support.

</details>

---

### Problem 51 — Strict Mode Double Invocation

```jsx
// In development with React.StrictMode
function App() {
  React.useEffect(() => {
    console.log("MOUNT");
    return () => console.log("UNMOUNT");
  }, []);
}

// Logs:
// MOUNT
// UNMOUNT
// MOUNT
```

**Why does this happen? Is it a bug?**

<details>
<summary>Answer</summary>

**Not a bug — intentional React 18 behavior in development.**

**Why:** React StrictMode intentionally mounts, unmounts, and remounts components in development to surface bugs in effects that don't properly clean up. This simulates the upcoming React feature of offscreen/deferred rendering where components may mount/unmount without user seeing it.

**What it catches:**
```jsx
// Bug — subscribes twice without cleanup
React.useEffect(() => {
  eventBus.subscribe("update", handler); // subscribes on mount
  // no return → no cleanup
  // StrictMode: subscribes twice, never unsubscribes
}, []);

// Fix
React.useEffect(() => {
  eventBus.subscribe("update", handler);
  return () => eventBus.unsubscribe("update", handler); // cleanup
}, []);
```

**Key:** Only happens in development mode. Production mounts once. If your app breaks with double-mount in dev, your cleanup is missing.

</details>

---

### Problem 52 — Concurrent Features Gotcha

```jsx
function App() {
  const [items, setItems] = React.useState([]);
  const [isPending, startTransition] = React.useTransition();

  const addItem = () => {
    startTransition(() => {
      setItems(prev => [...prev, Date.now()]);
    });
  };

  console.log("RENDER", items.length);

  return <button onClick={addItem}>Add</button>;
}
```

**Can React render the component with intermediate states inside a transition? What does this mean for side effects?**

<details>
<summary>Answer</summary>

**Yes — React can render, throw away, and re-render a component multiple times during a transition.**

**In concurrent mode:** React may start rendering a transition, get interrupted by an urgent update, discard the work-in-progress render, and restart. This can cause:
- `console.log` to fire more than once per "conceptual render"
- `useEffect` runs only on committed renders (safe)
- `useLayoutEffect` runs only on committed renders (safe)
- `useState` init functions called multiple times if in lazy init

**What NOT to do inside render:**
```jsx
// Bad — side effect in render body
function App() {
  analytics.track("render"); // may fire multiple times!
  return <div />;
}
```

**Safe pattern:**
```jsx
// Effects run after commit — always once per visible render
React.useEffect(() => {
  analytics.track("render");
}, []);
```

</details>

---

### Problem 53 — Server Components vs Client Components

```jsx
// Next.js App Router
// page.tsx — by default a Server Component
export default async function Page() {
  const data = await db.query("SELECT * FROM posts"); // direct DB access!
  return <PostList posts={data} />;
}
```

**What can/can't Server Components do? When do you add `"use client"`?**

<details>
<summary>Answer</summary>

**Server Components (default in Next.js App Router):**
- ✓ Direct database/filesystem access
- ✓ Keep secrets server-side (no API keys in bundle)
- ✓ Reduce client bundle size (component code stays on server)
- ✓ Async/await at component level
- ✗ No useState, useEffect, or any hooks
- ✗ No event handlers (onClick, onChange)
- ✗ No browser APIs (window, document)
- ✗ No class components

**Add `"use client"` when:**
```jsx
"use client";

// Needs interactivity
function Counter() {
  const [count, setCount] = React.useState(0);
  return <button onClick={() => setCount(c => c + 1)}>{count}</button>;
}
```

**Hybrid pattern (ideal):**
```jsx
// Server Component — fetches data
async function Page() {
  const posts = await db.getPosts();
  return (
    <div>
      <PostList posts={posts} />      {/* server component */}
      <LikeButton postId={posts[0].id} /> {/* client component */}
    </div>
  );
}
```

Push `"use client"` as deep in the tree as possible to maximize server rendering.

</details>

---

### Problem 54 — Memory Leak Patterns

```jsx
function Chat({ roomId }) {
  const [messages, setMessages] = React.useState([]);

  React.useEffect(() => {
    const socket = new WebSocket(`ws://api/room/${roomId}`);
    socket.onmessage = (e) => {
      setMessages(prev => [...prev, JSON.parse(e.data)]);
    };
    // No cleanup!
  }, [roomId]);

  return <MessageList messages={messages} />;
}
```

**List all memory leaks. Fix them.**

<details>
<summary>Answer</summary>

**Leaks:**
1. WebSocket connection never closed on unmount or `roomId` change
2. `setMessages` called on unmounted component
3. Old WebSocket not closed when `roomId` changes (accumulates connections)
4. Event listener on old socket persists

**Fix:**
```jsx
React.useEffect(() => {
  let cancelled = false;
  const socket = new WebSocket(`ws://api/room/${roomId}`);

  socket.onmessage = (e) => {
    if (!cancelled) {
      setMessages(prev => [...prev, JSON.parse(e.data)]);
    }
  };

  socket.onerror = (e) => console.error("WebSocket error:", e);

  return () => {
    cancelled = true;
    socket.close(); // close connection
    socket.onmessage = null; // remove handler
  };
}, [roomId]); // effect re-runs when roomId changes — cleans up old socket first
```

**General leak checklist:**
- WebSockets, EventSources — close in cleanup
- `addEventListener` — `removeEventListener` in cleanup
- Timers — `clearInterval/clearTimeout` in cleanup
- External store subscriptions — unsubscribe in cleanup
- Observers (IntersectionObserver, MutationObserver) — `.disconnect()` in cleanup

</details>

---

### Problem 55 — Accessibility in React

```jsx
function Dropdown({ options, onSelect }) {
  const [open, setOpen] = React.useState(false);
  return (
    <div>
      <div onClick={() => setOpen(!open)}>Select option</div>
      {open && (
        <div>
          {options.map(opt => (
            <div key={opt.value} onClick={() => onSelect(opt)}>
              {opt.label}
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
```

**List all accessibility problems. Fix them.**

<details>
<summary>Answer</summary>

**Problems:**
- `<div>` instead of `<button>` — not keyboard focusable
- No ARIA roles — screen readers can't identify this as a listbox
- No keyboard navigation (arrow keys, Enter, Escape)
- No `aria-expanded`, `aria-haspopup`
- Click-only — mouse-only interaction

**Fix:**
```jsx
function Dropdown({ options, onSelect }) {
  const [open, setOpen] = React.useState(false);
  const [focused, setFocused] = React.useState(-1);

  const handleKeyDown = (e) => {
    if (e.key === "Enter" || e.key === " ") setOpen(o => !o);
    if (e.key === "Escape") setOpen(false);
    if (e.key === "ArrowDown") setFocused(f => Math.min(f + 1, options.length - 1));
    if (e.key === "ArrowUp") setFocused(f => Math.max(f - 1, 0));
  };

  return (
    <div role="combobox" aria-expanded={open} aria-haspopup="listbox">
      <button
        onClick={() => setOpen(o => !o)}
        onKeyDown={handleKeyDown}
        aria-label="Select option"
      >
        Select option
      </button>
      {open && (
        <ul role="listbox">
          {options.map((opt, i) => (
            <li
              key={opt.value}
              role="option"
              aria-selected={focused === i}
              tabIndex={0}
              onClick={() => onSelect(opt)}
              onKeyDown={e => e.key === "Enter" && onSelect(opt)}
            >
              {opt.label}
            </li>
          ))}
        </ul>
      )}
    </div>
  );
}
```

**Or:** Use Radix UI / Headless UI which handle all ARIA patterns correctly.

</details>

---

### Problem 56 — Testing: What to Test

```jsx
function LoginForm({ onSuccess }) {
  const [email, setEmail] = React.useState("");
  const [password, setPassword] = React.useState("");
  const [error, setError] = React.useState("");

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      await api.login(email, password);
      onSuccess();
    } catch {
      setError("Invalid credentials");
    }
  };

  return (
    <form onSubmit={handleSubmit}>
      <input type="email" value={email} onChange={e => setEmail(e.target.value)} />
      <input type="password" value={password} onChange={e => setPassword(e.target.value)} />
      {error && <p role="alert">{error}</p>}
      <button type="submit">Login</button>
    </form>
  );
}
```

**Write tests covering the important behaviors using React Testing Library.**

<details>
<summary>Answer</summary>

```jsx
import { render, screen, userEvent, waitFor } from "@testing-library/react";
import { vi } from "vitest";

// Mock the API
vi.mock("../api", () => ({ login: vi.fn() }));

describe("LoginForm", () => {
  it("calls onSuccess when login succeeds", async () => {
    api.login.mockResolvedValue({ token: "abc" });
    const onSuccess = vi.fn();
    render(<LoginForm onSuccess={onSuccess} />);

    await userEvent.type(screen.getByRole("textbox", { name: /email/i }), "test@test.com");
    await userEvent.type(screen.getByLabelText(/password/i), "secret123");
    await userEvent.click(screen.getByRole("button", { name: /login/i }));

    await waitFor(() => expect(onSuccess).toHaveBeenCalledOnce());
  });

  it("shows error message on failed login", async () => {
    api.login.mockRejectedValue(new Error("Invalid"));
    render(<LoginForm onSuccess={vi.fn()} />);

    await userEvent.type(screen.getByRole("textbox", { name: /email/i }), "bad@test.com");
    await userEvent.type(screen.getByLabelText(/password/i), "wrong");
    await userEvent.click(screen.getByRole("button", { name: /login/i }));

    expect(await screen.findByRole("alert")).toHaveTextContent("Invalid credentials");
  });
});
```

**Testing philosophy:**
- Test behavior, not implementation
- Query by role/label (like a user/screen reader), not by className/id
- Don't test internal state — test what the user sees
- Mock at the boundary (API layer), not at React internals

</details>

---

### Problem 57 — Performance Profiling

```jsx
// App feels slow. How do you systematically identify the problem?
```

**Walk through your profiling methodology.**

<details>
<summary>Answer</summary>

**Step-by-step:**

**1. React DevTools Profiler:**
- Enable "Record why each component rendered"
- Interact with the slow part
- Look for: components with long render bars, unexpected re-renders

**2. Find unnecessary re-renders:**
- Yellow/orange bars = re-rendered
- Check "why did this render?" — stale props? Context change?
- Fix with React.memo, useCallback, useMemo, split context

**3. Chrome DevTools Performance tab:**
- Record during slow interaction
- Look for Long Tasks (>50ms) blocking main thread
- Identify JS execution, layout/style recalculation, paint

**4. Check bundle size:**
- `npm run build -- --analyze`
- Webpack Bundle Analyzer
- Look for: large deps, duplicate packages, unneeded polyfills

**5. Network tab:**
- Waterfall — are requests sequential when they could be parallel?
- Response sizes — are you fetching too much data?
- Caching — are API responses being cached?

**Common culprits:**
- `filter/map` on large arrays in render without memoization
- New object/function references in render passed to memoized children
- Context provider causing tree-wide re-renders
- Missing virtualization for long lists
- Synchronous heavy computation blocking paint

</details>

---

### Problem 58 — Next.js SSR Hydration Mismatch

```jsx
// Next.js page
export default function Page() {
  const [isMounted, setIsMounted] = React.useState(false);

  return (
    <div>
      {isMounted ? "Client" : "Server"}
    </div>
  );
}
```

**Why does this cause a hydration error? How to fix?**

<details>
<summary>Answer</summary>

**Why:** SSR renders "Server". Client hydrates expecting to match — but `isMounted` is still `false` during hydration. Once hydration finishes, `useEffect` sets `isMounted = true`, changing content to "Client". But the hydration mismatch is already flagged because the initial render doesn't match the server HTML.

**Fix 1 — useEffect for client-only content:**
```jsx
const [hasMounted, setHasMounted] = React.useState(false);
React.useEffect(() => setHasMounted(true), []);

if (!hasMounted) return null; // or server-safe fallback
return <div>Client-only content</div>;
```

**Fix 2 — suppressHydrationWarning (narrow use):**
```jsx
<span suppressHydrationWarning>
  {new Date().toLocaleTimeString()}
</span>
```

**Fix 3 — dynamic import with ssr: false (Next.js):**
```jsx
const ClientOnlyComponent = dynamic(() => import("./ClientComponent"), {
  ssr: false
});
```

**Root cause:** Anything that differs between server and client (window, localStorage, Math.random(), Date.now()) causes mismatches. Keep SSR output predictable.

</details>

---

### Problem 59 — Module Federation / Micro-frontends

```jsx
// Shell app loading a remote module
const RemoteButton = React.lazy(() =>
  import("remoteApp/Button")
);
```

**What is Module Federation? When would you use it?**

<details>
<summary>Answer</summary>

**Module Federation (Webpack 5):** Allows multiple separate builds to share code at runtime. Each "remote" app exposes modules. The "host/shell" app consumes them dynamically.

**Use when:**
- Multiple teams own separate frontend applications
- Independent deployment cycles needed per team
- Different tech stacks (React 17 + React 18 coexisting)
- Large monolithic frontend being broken apart

**Architecture:**
```
Shell App (host)
├── loads → TeamA/ProductCatalog (remote)
├── loads → TeamB/Checkout (remote)
└── loads → TeamC/UserProfile (remote)
```

Each remote deploys independently. Shell picks up latest at runtime.

**Challenges:**
- Shared dependency versioning (React must be singleton)
- Type sharing across remotes
- Testing integration points
- Network failures when remotes unavailable

```js
// webpack.config.js (remote app)
new ModuleFederationPlugin({
  name: "teamA",
  filename: "remoteEntry.js",
  exposes: {
    "./ProductCatalog": "./src/ProductCatalog",
  },
  shared: { react: { singleton: true }, "react-dom": { singleton: true } }
});
```

**2025 alternative:** Vite's `@originjs/vite-plugin-federation` or native ESM sharing patterns.

</details>

---

### Problem 60 — Advanced TypeScript + React Patterns

```tsx
// Problem: Generic table component that's type-safe
function Table({ data, columns }) { // no types!
  return (
    <table>
      {data.map(row => (
        <tr>{columns.map(col => <td>{row[col.key]}</td>)}</tr>
      ))}
    </table>
  );
}
```

**Make this fully type-safe with generics.**

<details>
<summary>Answer</summary>

```tsx
interface Column<T> {
  key: keyof T;
  header: string;
  render?: (value: T[keyof T], row: T) => React.ReactNode;
}

interface TableProps<T extends Record<string, unknown>> {
  data: T[];
  columns: Column<T>[];
  getRowKey: (row: T) => string | number;
}

function Table<T extends Record<string, unknown>>({
  data,
  columns,
  getRowKey,
}: TableProps<T>) {
  return (
    <table>
      <thead>
        <tr>{columns.map(col => <th key={String(col.key)}>{col.header}</th>)}</tr>
      </thead>
      <tbody>
        {data.map(row => (
          <tr key={getRowKey(row)}>
            {columns.map(col => (
              <td key={String(col.key)}>
                {col.render ? col.render(row[col.key], row) : String(row[col.key])}
              </td>
            ))}
          </tr>
        ))}
      </tbody>
    </table>
  );
}

// Usage — fully typed, col.key must be a key of User
interface User { id: number; name: string; email: string; }

<Table<User>
  data={users}
  getRowKey={u => u.id}
  columns={[
    { key: "name", header: "Name" },
    { key: "email", header: "Email", render: (val) => <a href={`mailto:${val}`}>{val}</a> }
  ]}
/>
```

TypeScript infers `T = User`, validates that `key` must be `"id" | "name" | "email"`.

</details>

---

## Quick Reference Cheat Sheet

| Scenario | Solution |
|---|---|
| Object in dep array causes infinite loop | Depend on primitive fields |
| Child re-renders despite React.memo | useCallback for function props |
| Stale value in setInterval | useRef or functional setState |
| Async stale closure | Functional updater `setState(prev => ...)` |
| Race condition in fetch | AbortController + cleanup flag |
| Context causing tree re-renders | Split contexts, memoize value |
| Expensive computation every render | useMemo with correct deps |
| Input lag from heavy list filter | useTransition / useDeferredValue |
| Large list performance | react-window / TanStack Virtual |
| Multiple API calls for same data | TanStack Query / deduplicate |
| Redux re-rendering on unrelated changes | Reselect + createSelector |
| Redux direct mutation | Return new state / use RTK+Immer |
| Form without library | useReducer state machine |
| Prop drilling | Context / Composition / Zustand |
| Hydration mismatch | useEffect-guarded client content |
| Component too large | Extract hooks + sub-components |
| Loading state bugs | State machine (useReducer) |
| Effect runs on every render | Stabilize deps (primitive values) |

---

*Built for developers who want to reason deeply about React, not just pass interviews.*
