package SOLID.problems.Pluggable_Notification_System;

public class EmailNotification implements Notification {
    @Override
    public void sendNotification(String message) {
        System.out.println("Sending Email notification: " + message);
    }
    @Override
    public String getNotificationType() {
        return "Email";
    }
    
}
