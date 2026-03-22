package SOLID.problems.Pluggable_Notification_System;


public class SmsNotifcation implements Notification {
    @Override
    public void sendNotification(String message) {
        System.out.println("Sending SMS notification: " + message);
    }

    @Override
    public String getNotificationType() {
        return "SMS";
    }

}
