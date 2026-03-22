package SOLID.problems.Pluggable_Notification_System;

import java.util.ArrayList;

public class User {
    ArrayList<Notification> notifications;
    public User() {
        notifications = new ArrayList<>();
    }
    public void addNotification(Notification notification) {
        notifications.add(notification);
    }
}



