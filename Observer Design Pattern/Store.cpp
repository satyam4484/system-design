#include "./Observable/StocksObservable.cpp"
#include "./Observable/IphoneObservable.cpp"
#include "./Observer/NotificationAlertObserver.cpp"
#include "./Observer/EmailAlertObserver.cpp"

// using namespace std;

int main() {
    // creating the stocks for iphone using iphoneobservable (Dependency inversion)
    stocksObservable *iPhoneStock = new IphoneObservable();

    // making the users with email notifier
    NotificationAlertObserver *obj1=new EmailAlertObserver("sa@gmail.com",iPhoneStock);
    NotificationAlertObserver *obj2=new EmailAlertObserver("skman@gmail.com",iPhoneStock);

    // subscribing the user
    iPhoneStock->add(obj1);
    iPhoneStock->add(obj2);

    // new products are added so notify the users
    iPhoneStock->setCount(10);

    // unsubsribe the particular user
    iPhoneStock->remove(obj2);

    // again new stock has been arrived
    iPhoneStock->setCount(15);
    return 0;
}