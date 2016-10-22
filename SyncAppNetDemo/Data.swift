import Foundation
import CoreData

@objc(Data)
class Data: NSManagedObject {
    @NSManaged var text: String
    @NSManaged var id: String
    @NSManaged var createdAt: TimeInterval
    @NSManaged var user: User
    
}
