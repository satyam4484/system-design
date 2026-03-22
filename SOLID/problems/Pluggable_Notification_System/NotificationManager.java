package SOLID.problems.Pluggable_Notification_System;

public class NotificationManager {
    public void sendNotification(User user, String message) {
        for (Notification notification : user.notifications) {
            try {
                notification.sendNotification(message);
                return; // Exit after successful notification
            } catch (Exception e) {
                System.out.println("Failed to send notification: " + notification.getNotificationType());
                System.out.println("Trying again with another notification method...");
            }
        }

    }
}
