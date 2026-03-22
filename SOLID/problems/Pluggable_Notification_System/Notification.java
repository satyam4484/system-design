package SOLID.problems.Pluggable_Notification_System;

public interface Notification {
    void sendNotification(String message);
    String getNotificationType();
}