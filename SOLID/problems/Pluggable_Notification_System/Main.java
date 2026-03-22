package SOLID.problems.Pluggable_Notification_System;

public class Main {
    
    public static void main(String[] args) {
       NotificationManager notificationManager = new NotificationManager();
       User user = new User();
       user.addNotification(new EmailNotification());
       user.addNotification(new SmsNotifcation());
       notificationManager.sendNotification(user, "hello from developer");
    }
}
