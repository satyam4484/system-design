// =============================================================
// Abstract Factory Design


// Product interfaces
interface Button {
    void click();
}

interface Menu {
    void open();
}

interface Slider {
    void slide();
}

// Factory interface
interface UIFactory {
    Button createButton();
    Menu createMenu();
    Slider createSlider();
}

// Web concrete products
class WebButton implements Button {
    public void click() {
        System.out.println("Web Button clicked!");
    }
}

class WebMenu implements Menu {
    public void open() {
        System.out.println("Web Menu opened!");
    }
}

class WebSlider implements Slider {
    public void slide() {
        System.out.println("Web Slider sliding!");
    }
}

class MobileButton implements Button {
    public void click() {
        System.out.println("Mobile Button clicked!");
    }
}
class MobileMenu implements Menu {
    public void open() {
        System.out.println("Mobile Menu opened!");
    }
}

class MobileSlider implements Slider {
    public void slide() {
        System.out.println("Web Slider sliding!");
    }
}

class MobileUIFactoruy implements UIFactory{
    public Button createButton() {
        return new MobileButton();
    }

    public Menu createMenu() {
        return new MobileMenu();
    }

    public Slider createSlider() {
        return new MobileSlider();
    }

}


// Web factory
class WebUIFactory implements UIFactory {
    public Button createButton() {
        return new WebButton();
    }

    public Menu createMenu() {
        return new WebMenu();
    }

    public Slider createSlider() {
        return new WebSlider();
    }
};

// =============================================================

// =============================================================
// Factory design pattern
class UIFactoryProvider {
    public static UIFactory getFactory(String platform) {
        if (platform.equalsIgnoreCase("WEB")) {
            return new WebUIFactory();
        } else if (platform.equalsIgnoreCase("MOBILE")) {
            return new MobileUIFactoruy();
        }
        return null;
    }
}
// =============================================================

// Usage example
public class Main {
    public static void main(String[] args) {
        UIFactory factory = UIFactoryProvider.getFactory("WEB");
        
        Button button = factory.createButton();
        Menu menu = factory.createMenu();
        Slider slider = factory.createSlider();
        
        button.click();
        menu.open();
        slider.slide();
    }
}