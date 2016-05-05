import UIKit
import CoreData
import DATAStack

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    var window: UIWindow?
    lazy var dataStack: DATAStack = DATAStack(modelName: "AppNet")

    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        self.window = UIWindow(frame: UIScreen.mainScreen().bounds)
        self.window?.rootViewController = UINavigationController(rootViewController: ViewController(dataStack: self.dataStack))
        self.window?.makeKeyAndVisible()

        return true
    }

    func applicationDidEnterBackground(application: UIApplication) {
        self.dataStack.persist(nil)
    }

    func applicationWillTerminate(application: UIApplication) {
        self.dataStack.persist(nil)
    }
}

