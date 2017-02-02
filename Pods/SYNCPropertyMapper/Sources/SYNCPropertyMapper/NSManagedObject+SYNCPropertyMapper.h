@import CoreData;

NS_ASSUME_NONNULL_BEGIN

static NSString * const SYNCPropertyMapperCustomRemoteKey = @"hyper.remoteKey";
static NSString * const SYNCPropertyMapperNonExportableKey = @"hyper.nonExportable";

typedef NS_ENUM(NSInteger, SYNCPropertyMapperRelationshipType) {
    SYNCPropertyMapperRelationshipTypeNone = 0,
    SYNCPropertyMapperRelationshipTypeArray,
    SYNCPropertyMapperRelationshipTypeNested
};

@interface NSManagedObject (SYNCPropertyMapper)

/*! Fills the NSManagedObject with the contents of the dictionary
 *  using a convention-over-configuration paradigm mapping the
 *  Core Data attributes to their conterparts in JSON using snake_case.
 */
- (void)hyp_fillWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

/*! Creates a NSDictionary of values based on the NSManagedObject subclass that can be serialized by NSJSONSerialization. Includes relationships to other models using Ruby on Rail's nested attributes model.
 *  NSDate objects will be stringified to the ISO-8601 standard.
 * \return NSDictionary of values that can be serialized
 */
- (NSDictionary<NSString *, id> *)hyp_dictionary;

/*! Creates a NSDictionary of values based on the NSManagedObject subclass that can be serialized by NSJSONSerialization. Could include relationships to other models.
 *  NSDate objects will be stringified to the ISO-8601 standard.
 * \param relationshipType - It indicates wheter the result dictionary should include no relationships, nested attributes or normal attributes
 * \return NSDictionary of values that can be serialized
 */
- (NSDictionary<NSString *, id> *)hyp_dictionaryUsingRelationshipType:(SYNCPropertyMapperRelationshipType)relationshipType;

/*! Creates a NSDictionary of values based on the NSManagedObject subclass that can be serialized by NSJSONSerialization. Includes relationships to other models using Ruby on Rail's nested attributes model.
 * \param dateFormatter - A custom date formatter that turns NSDate objects into NSString objects. Do not pass nil, instead use the 'hyp_dictionary' method
 * \return NSDictionary of values that can be serialized
 */
- (NSDictionary<NSString *, id> *)hyp_dictionaryWithDateFormatter:(NSDateFormatter *)dateFormatter;

/*! Creates a NSDictionary of values based on the NSManagedObject subclass that can be serialized by NSJSONSerialization. Could include relationships to other models using Ruby on Rail's nested attributes model.
 * \param dateFormatter - A custom date formatter that turns NSDate objects into NSString objects. Do not pass nil, instead use the 'hyp_dictionary' method
 * \param relationshipType - It indicates wheter the result dictionary should include no relationships, nested attributes or normal attributes
 * \return NSDictionary of values that can be serialized
 */
- (NSDictionary<NSString *, id> *)hyp_dictionaryWithDateFormatter:(NSDateFormatter *)dateFormatter usingRelationshipType:(SYNCPropertyMapperRelationshipType)relationshipType;

/*! Creates a NSDictionary of values based on the NSManagedObject subclass that can be serialized by NSJSONSerialization. Could include relationships to other models using Ruby on Rail's nested attributes model.
 * \param dateFormatter - A custom date formatter that turns NSDate objects into NSString objects. Do not pass nil, instead use the 'hyp_dictionary' method
 * \param parent - The parent of the managed object
 * \param relationshipType - It indicates wheter the result dictionary should include no relationships, nested attributes or normal attributes
 * \return NSDictionary of values that can be serialized
 */
- (NSDictionary<NSString *, id> *)hyp_dictionaryWithDateFormatter:(NSDateFormatter *)dateFormatter parent:( NSManagedObject * _Nullable )parent usingRelationshipType:(SYNCPropertyMapperRelationshipType)relationshipType;

@end

NS_ASSUME_NONNULL_END
