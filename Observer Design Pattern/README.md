   # Stock Notification System for E-commerce Platform

   ## Overview
   This project implements a stock notification system for an e-commerce platform, focusing on notifying users via email whenever the stock of a particular product, such as iPhones, is updated. The system utilizes the Observer design pattern to manage subscribers and notify them of changes in stock levels.

   ## Features
   - Allows users to subscribe and unsubscribe from receiving notifications for specific products.
   - Sends email notifications to subscribed users when the stock count of a product is updated.
   - Supports multiple products with independent subscriber lists.

   ## Components
   1. **Observable Interface (`stocksObservable`):** Defines methods to manage subscribers and notify them of changes in stock levels.
   2. **Concrete Observable Class (`IphoneObservable`):** Implements the `stocksObservable` interface for iPhones. Maintains a list of subscribers and notifies them whenever the stock count of iPhones is updated.
   3. **Observer Interface (`NotificationAlertObserver`):** Defines a method `update()` that observers implement to receive notifications.
   4. **Concrete Observer Class (`EmailAlertObserver`):** Implements the `NotificationAlertObserver` interface and provides functionality to send email notifications to subscribed users.

   ## Usage
   1. **Subscription:**
      - Create instances of `EmailAlertObserver` for users who wish to subscribe to notifications.
      - Subscribe users to specific product observables using the `add()` method of the respective observable.

   2. **Notification:**
      - Whenever the stock count of a product changes, call the `setCount()` method of the corresponding observable with the new count.
      - Subscribed users will receive email notifications automatically.
