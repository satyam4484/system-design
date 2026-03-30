
# 🎯 Adapter Design Pattern – Problem Statement

## 🧩 Problem: Payment Gateway Integration

You are building an **e-commerce application**.

Currently, your system supports only one payment gateway:

* `PayPalService` → works with method:

```java
void makePayment(double amount);
```

---

## 🚧 New Requirement

Your business team wants to integrate **Stripe** and **Razorpay**.

But here’s the challenge:

* Stripe API:

```java
void payInDollars(double amount);
```

* Razorpay API:

```java
void processPaymentINR(double amount);
```

👉 These APIs are **incompatible** with your existing system.

---

## ❗ Constraint

* You **cannot modify existing classes** (PayPal, Stripe, Razorpay)
* Your existing system expects:

```java
interface Payment {
    void pay(double amount);
}
```

---

## 🎯 Goal

Design a system such that:

* All payment methods work through a **common interface (`Payment`)**
* You can plug in new gateways **without changing existing code**
* Your system remains **extensible and clean**

---

## 💡 What You Need to Think

As a candidate, you should design:

1. A **target interface** → `Payment`
2. Existing incompatible classes → Stripe, Razorpay
3. An **Adapter layer**:

   * `StripeAdapter`
   * `RazorpayAdapter`

---

## 🧠 Expected Thinking (Interview Signal)

* “I will wrap incompatible APIs using adapters”
* “Core system will depend only on `Payment` interface”
* “Adapters translate calls → system stays unchanged”

---

## 🔥 Bonus Follow-ups (Interviewer may ask)

1. How would you add currency conversion?
2. What if APIs are async?
3. How would you handle failures/retries?
4. Can you combine this with Factory?
