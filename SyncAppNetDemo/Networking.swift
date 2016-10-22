import UIKit
import DATAStack
import Sync
import Alamofire

class Networking: NSObject {
    let AppNetURL = "https://api.app.net/posts/stream/global"
    let dataStack: DATAStack

    required init(dataStack: DATAStack) {
        self.dataStack = dataStack
    }

    func fetchItems(_ completion: @escaping (NSError?) -> Void) {
        Alamofire.request(AppNetURL).responseJSON { response in
            let data = response.result.value as! [String : Any]

            Sync.changes(data["data"] as! [[String : Any]], inEntityNamed: "Data", dataStack: self.dataStack) { error in
                completion(error)
            }
        }
    }

    /*
    An example on how to properly receive notifications of changes. Includes a local "global.json" so you can modify it to try it,
    but it can easily work with your own JSON too. Please use notifications to react to changes, not to modify the returned elements
    since that would be unsafe.
    */
    func fetchLocalItems(_ completion: @escaping (NSError?) -> Void) {
        let url = URL(string: "global.json")!
        let filePath = Bundle.main.path(forResource: url.deletingPathExtension().absoluteString, ofType: url.pathExtension)!
        let data = try! Foundation.Data(contentsOf: URL(fileURLWithPath: filePath))
        let json = try! JSONSerialization.jsonObject(with: data, options: []) as! [String: AnyObject]
        self.dataStack.performInNewBackgroundContext { backgroundContext in
            NotificationCenter.default.addObserver(self, selector: #selector(Networking.changeNotification(_:)), name: .NSManagedObjectContextObjectsDidChange, object: backgroundContext)

            Sync.changes(json["data"] as! Array, inEntityNamed: "Data", predicate: nil, parent: nil, inContext: backgroundContext, dataStack: self.dataStack, completion: { error in
                NotificationCenter.default.removeObserver(self, name: .NSManagedObjectContextObjectsDidChange, object: nil)
                completion(error)
            })
        }
    }

    func changeNotification(_ notification: Notification) {
        let updatedObjects = notification.userInfo?[NSUpdatedObjectsKey]
        let deletedObjects = notification.userInfo?[NSDeletedObjectsKey]
        let insertedObjects = notification.userInfo?[NSInsertedObjectsKey]
        print("updatedObjects: \(updatedObjects)")
        print("deletedObjects: \(deletedObjects)")
        print("insertedObjects: \(insertedObjects)")
    }
}
