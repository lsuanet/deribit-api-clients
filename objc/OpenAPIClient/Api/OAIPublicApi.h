#import <Foundation/Foundation.h>
#import "OAIApi.h"

/**
* Deribit API
* #Overview  Deribit provides three different interfaces to access the API:  * [JSON-RPC over Websocket](#json-rpc) * [JSON-RPC over HTTP](#json-rpc) * [FIX](#fix-api) (Financial Information eXchange)  With the API Console you can use and test the JSON-RPC API, both via HTTP and  via Websocket. To visit the API console, go to __Account > API tab >  API Console tab.__   ##Naming Deribit tradeable assets or instruments use the following system of naming:  |Kind|Examples|Template|Comments| |----|--------|--------|--------| |Future|<code>BTC-25MAR16</code>, <code>BTC-5AUG16</code>|<code>BTC-DMMMYY</code>|<code>BTC</code> is currency, <code>DMMMYY</code> is expiration date, <code>D</code> stands for day of month (1 or 2 digits), <code>MMM</code> - month (3 first letters in English), <code>YY</code> stands for year.| |Perpetual|<code>BTC-PERPETUAL</code>                        ||Perpetual contract for currency <code>BTC</code>.| |Option|<code>BTC-25MAR16-420-C</code>, <code>BTC-5AUG16-580-P</code>|<code>BTC-DMMMYY-STRIKE-K</code>|<code>STRIKE</code> is option strike price in USD. Template <code>K</code> is option kind: <code>C</code> for call options or <code>P</code> for put options.|   # JSON-RPC JSON-RPC is a light-weight remote procedure call (RPC) protocol. The  [JSON-RPC specification](https://www.jsonrpc.org/specification) defines the data structures that are used for the messages that are exchanged between client and server, as well as the rules around their processing. JSON-RPC uses JSON (RFC 4627) as data format.  JSON-RPC is transport agnostic: it does not specify which transport mechanism must be used. The Deribit API supports both Websocket (preferred) and HTTP (with limitations: subscriptions are not supported over HTTP).  ## Request messages > An example of a request message:  ```json {     \"jsonrpc\": \"2.0\",     \"id\": 8066,     \"method\": \"public/ticker\",     \"params\": {         \"instrument\": \"BTC-24AUG18-6500-P\"     } } ```  According to the JSON-RPC sepcification the requests must be JSON objects with the following fields.  |Name|Type|Description| |----|----|-----------| |jsonrpc|string|The version of the JSON-RPC spec: \"2.0\"| |id|integer or string|An identifier of the request. If it is included, then the response will contain the same identifier| |method|string|The method to be invoked| |params|object|The parameters values for the method. The field names must match with the expected parameter names. The parameters that are expected are described in the documentation for the methods, below.|  <aside class=\"warning\"> The JSON-RPC specification describes two features that are currently not supported by the API:  <ul> <li>Specification of parameter values by position</li> <li>Batch requests</li> </ul>  </aside>   ## Response messages > An example of a response message:  ```json {     \"jsonrpc\": \"2.0\",     \"id\": 5239,     \"testnet\": false,     \"result\": [         {             \"currency\": \"BTC\",             \"currencyLong\": \"Bitcoin\",             \"minConfirmation\": 2,             \"txFee\": 0.0006,             \"isActive\": true,             \"coinType\": \"BITCOIN\",             \"baseAddress\": null         }     ],     \"usIn\": 1535043730126248,     \"usOut\": 1535043730126250,     \"usDiff\": 2 } ```  The JSON-RPC API always responds with a JSON object with the following fields.   |Name|Type|Description| |----|----|-----------| |id|integer|This is the same id that was sent in the request.| |result|any|If successful, the result of the API call. The format for the result is described with each method.| |error|error object|Only present if there was an error invoking the method. The error object is described below.| |testnet|boolean|Indicates whether the API in use is actually the test API.  <code>false</code> for production server, <code>true</code> for test server.| |usIn|integer|The timestamp when the requests was received (microseconds since the Unix epoch)| |usOut|integer|The timestamp when the response was sent (microseconds since the Unix epoch)| |usDiff|integer|The number of microseconds that was spent handling the request|  <aside class=\"notice\"> The fields <code>testnet</code>, <code>usIn</code>, <code>usOut</code> and <code>usDiff</code> are not part of the JSON-RPC standard.  <p>In order not to clutter the examples they will generally be omitted from the example code.</p> </aside>  > An example of a response with an error:  ```json {     \"jsonrpc\": \"2.0\",     \"id\": 8163,     \"error\": {         \"code\": 11050,         \"message\": \"bad_request\"     },     \"testnet\": false,     \"usIn\": 1535037392434763,     \"usOut\": 1535037392448119,     \"usDiff\": 13356 } ``` In case of an error the response message will contain the error field, with as value an object with the following with the following fields:  |Name|Type|Description |----|----|-----------| |code|integer|A number that indicates the kind of error.| |message|string|A short description that indicates the kind of error.| |data|any|Additional data about the error. This field may be omitted.|  ## Notifications  > An example of a notification:  ```json {     \"jsonrpc\": \"2.0\",     \"method\": \"subscription\",     \"params\": {         \"channel\": \"deribit_price_index.btc_usd\",         \"data\": {             \"timestamp\": 1535098298227,             \"price\": 6521.17,             \"index_name\": \"btc_usd\"         }     } } ```  API users can subscribe to certain types of notifications. This means that they will receive JSON-RPC notification-messages from the server when certain events occur, such as changes to the index price or changes to the order book for a certain instrument.   The API methods [public/subscribe](#public-subscribe) and [private/subscribe](#private-subscribe) are used to set up a subscription. Since HTTP does not support the sending of messages from server to client, these methods are only availble when using the Websocket transport mechanism.  At the moment of subscription a \"channel\" must be specified. The channel determines the type of events that will be received.  See [Subscriptions](#subscriptions) for more details about the channels.  In accordance with the JSON-RPC specification, the format of a notification  is that of a request message without an <code>id</code> field. The value of the <code>method</code> field will always be <code>\"subscription\"</code>. The <code>params</code> field will always be an object with 2 members: <code>channel</code> and <code>data</code>. The value of the <code>channel</code> member is the name of the channel (a string). The value of the <code>data</code> member is an object that contains data  that is specific for the channel.   ## Authentication  > An example of a JSON request with token:  ```json {     \"id\": 5647,     \"method\": \"private/get_subaccounts\",     \"params\": {         \"access_token\": \"67SVutDoVZSzkUStHSuk51WntMNBJ5mh5DYZhwzpiqDF\"     } } ```  The API consists of `public` and `private` methods. The public methods do not require authentication. The private methods use OAuth 2.0 authentication. This means that a valid OAuth access token must be included in the request, which can get achived by calling method [public/auth](#public-auth).  When the token was assigned to the user, it should be passed along, with other request parameters, back to the server:  |Connection type|Access token placement |----|-----------| |**Websocket**|Inside request JSON parameters, as an `access_token` field| |**HTTP (REST)**|Header `Authorization: bearer ```Token``` ` value|  ### Additional authorization method - basic user credentials  <span style=\"color:red\"><b> ! Not recommended - however, it could be useful for quick testing API</b></span></br>  Every `private` method could be accessed by providing, inside HTTP `Authorization: Basic XXX` header, values with user `ClientId` and assigned `ClientSecret` (both values can be found on the API page on the Deribit website) encoded with `Base64`:  <code>Authorization: Basic BASE64(`ClientId` + `:` + `ClientSecret`)</code>   ### Additional authorization method - Deribit signature credentials  The Derbit service provides dedicated authorization method, which harness user generated signature to increase security level for passing request data. Generated value is passed inside `Authorization` header, coded as:  <code>Authorization: deri-hmac-sha256 id=```ClientId```,ts=```Timestamp```,sig=```Signature```,nonce=```Nonce```</code>  where:  |Deribit credential|Description |----|-----------| |*ClientId*|Can be found on the API page on the Deribit website| |*Timestamp*|Time when the request was generated - given as **miliseconds**. It's valid for **60 seconds** since generation, after that time any request with an old timestamp will be rejected.| |*Signature*|Value for signature calculated as described below | |*Nonce*|Single usage, user generated initialization vector for the server token|  The signature is generated by the following formula:  <code> Signature = HEX_STRING( HMAC-SHA256( ClientSecret, StringToSign ) );</code></br>  <code> StringToSign =  Timestamp + \"\\n\" + Nonce + \"\\n\" + RequestData;</code></br>  <code> RequestData =  UPPERCASE(HTTP_METHOD())  + \"\\n\" + URI() + \"\\n\" + RequestBody + \"\\n\";</code></br>   e.g. (using shell with ```openssl``` tool):  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientId=AAAAAAAAAAA</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientSecret=ABCD</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Timestamp=$( date +%s000 )</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Nonce=$( cat /dev/urandom | tr -dc 'a-z0-9' | head -c8 )</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;URI=\"/api/v2/private/get_account_summary?currency=BTC\"</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;HttpMethod=GET</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Body=\"\"</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Signature=$( echo -ne \"${Timestamp}\\n${Nonce}\\n${HttpMethod}\\n${URI}\\n${Body}\\n\" | openssl sha256 -r -hmac \"$ClientSecret\" | cut -f1 -d' ' )</code></br></br> <code>&nbsp;&nbsp;&nbsp;&nbsp;echo $Signature</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;shell output> ea40d5e5e4fae235ab22b61da98121fbf4acdc06db03d632e23c66bcccb90d2c  (**WARNING**: Exact value depends on current timestamp and client credentials</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;curl -s -X ${HttpMethod} -H \"Authorization: deri-hmac-sha256 id=${ClientId},ts=${Timestamp},nonce=${Nonce},sig=${Signature}\" \"https://www.deribit.com${URI}\"</code></br></br>    ### Additional authorization method - signature credentials (WebSocket API)  When connecting through Websocket, user can request for authorization using ```client_credential``` method, which requires providing following parameters (as a part of JSON request):  |JSON parameter|Description |----|-----------| |*grant_type*|Must be **client_signature**| |*client_id*|Can be found on the API page on the Deribit website| |*timestamp*|Time when the request was generated - given as **miliseconds**. It's valid for **60 seconds** since generation, after that time any request with an old timestamp will be rejected.| |*signature*|Value for signature calculated as described below | |*nonce*|Single usage, user generated initialization vector for the server token| |*data*|**Optional** field, which contains any user specific value|  The signature is generated by the following formula:  <code> StringToSign =  Timestamp + \"\\n\" + Nonce + \"\\n\" + Data;</code></br>  <code> Signature = HEX_STRING( HMAC-SHA256( ClientSecret, StringToSign ) );</code></br>   e.g. (using shell with ```openssl``` tool):  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientId=AAAAAAAAAAA</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientSecret=ABCD</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Timestamp=$( date +%s000 ) # e.g. 1554883365000 </code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Nonce=$( cat /dev/urandom | tr -dc 'a-z0-9' | head -c8 ) # e.g. fdbmmz79 </code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Data=\"\"</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Signature=$( echo -ne \"${Timestamp}\\n${Nonce}\\n${Data}\\n\" | openssl sha256 -r -hmac \"$ClientSecret\" | cut -f1 -d' ' )</code></br></br> <code>&nbsp;&nbsp;&nbsp;&nbsp;echo $Signature</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;shell output> e20c9cd5639d41f8bbc88f4d699c4baf94a4f0ee320e9a116b72743c449eb994  (**WARNING**: Exact value depends on current timestamp and client credentials</code></br></br>   You can also check the signature value using some online tools like, e.g: [https://codebeautify.org/hmac-generator](https://codebeautify.org/hmac-generator) (but don't forget about adding *newline* after each part of the hashed text and remember that you **should use** it only with your **test credentials**).   Here's a sample JSON request created using the values from the example above:  <code> {                            </br> &nbsp;&nbsp;\"jsonrpc\" : \"2.0\",         </br> &nbsp;&nbsp;\"id\" : 9929,               </br> &nbsp;&nbsp;\"method\" : \"public/auth\",  </br> &nbsp;&nbsp;\"params\" :                 </br> &nbsp;&nbsp;{                        </br> &nbsp;&nbsp;&nbsp;&nbsp;\"grant_type\" : \"client_signature\",   </br> &nbsp;&nbsp;&nbsp;&nbsp;\"client_id\" : \"AAAAAAAAAAA\",         </br> &nbsp;&nbsp;&nbsp;&nbsp;\"timestamp\": \"1554883365000\",        </br> &nbsp;&nbsp;&nbsp;&nbsp;\"nonce\": \"fdbmmz79\",                 </br> &nbsp;&nbsp;&nbsp;&nbsp;\"data\": \"\",                          </br> &nbsp;&nbsp;&nbsp;&nbsp;\"signature\" : \"e20c9cd5639d41f8bbc88f4d699c4baf94a4f0ee320e9a116b72743c449eb994\"  </br> &nbsp;&nbsp;}                        </br> }                            </br> </code>   ### Access scope  When asking for `access token` user can provide the required access level (called `scope`) which defines what type of functionality he/she wants to use, and whether requests are only going to check for some data or also to update them.  Scopes are required and checked for `private` methods, so if you plan to use only `public` information you can stay with values assigned by default.  |Scope|Description |----|-----------| |*account:read*|Access to **account** methods - read only data| |*account:read_write*|Access to **account** methods - allows to manage account settings, add subaccounts, etc.| |*trade:read*|Access to **trade** methods - read only data| |*trade:read_write*|Access to **trade** methods - required to create and modify orders| |*wallet:read*|Access to **wallet** methods - read only data| |*wallet:read_write*|Access to **wallet** methods - allows to withdraw, generate new deposit address, etc.| |*wallet:none*, *account:none*, *trade:none*|Blocked access to specified functionality|    <span style=\"color:red\">**NOTICE:**</span> Depending on choosing an authentication method (```grant type```) some scopes could be narrowed by the server. e.g. when ```grant_type = client_credentials``` and ```scope = wallet:read_write``` it's modified by the server as ```scope = wallet:read```\"   ## JSON-RPC over websocket Websocket is the prefered transport mechanism for the JSON-RPC API, because it is faster and because it can support [subscriptions](#subscriptions) and [cancel on disconnect](#private-enable_cancel_on_disconnect). The code examples that can be found next to each of the methods show how websockets can be used from Python or Javascript/node.js.  ## JSON-RPC over HTTP Besides websockets it is also possible to use the API via HTTP. The code examples for 'shell' show how this can be done using curl. Note that subscriptions and cancel on disconnect are not supported via HTTP.  #Methods 
*
* OpenAPI spec version: 2.0.0
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/



@interface OAIPublicApi: NSObject <OAIApi>

extern NSString* kOAIPublicApiErrorDomain;
extern NSInteger kOAIPublicApiMissingParamErrorCode;

-(instancetype) initWithApiClient:(OAIApiClient *)apiClient NS_DESIGNATED_INITIALIZER;

/// Authenticate
/// Retrieve an Oauth access token, to be used for authentication of 'private' requests.  Three methods of authentication are supported:  - <code>password</code> - using email and and password as when logging on to the website - <code>client_credentials</code> - using the access key and access secret that can be found on the API page on the website - <code>client_signature</code> - using the access key that can be found on the API page on the website and user generated signature. The signature is calculated using some fields provided in the request, using formula described here [Deribit signature credentials](#additional-authorization-method-deribit-signature-credentials) - <code>refresh_token</code> - using a refresh token that was received from an earlier invocation  The response will contain an access token, expiration period (number of seconds that the token is valid) and a refresh token that can be used to get a new set of tokens. 
///
/// @param grantType Method of authentication
/// @param username Required for grant type &#x60;password&#x60;
/// @param password Required for grant type &#x60;password&#x60;
/// @param clientId Required for grant type &#x60;client_credentials&#x60; and &#x60;client_signature&#x60;
/// @param clientSecret Required for grant type &#x60;client_credentials&#x60;
/// @param refreshToken Required for grant type &#x60;refresh_token&#x60;
/// @param timestamp Required for grant type &#x60;client_signature&#x60;, provides time when request has been generated
/// @param signature Required for grant type &#x60;client_signature&#x60;; it&#39;s a cryptographic signature calculated over provided fields using user **secret key**. The signature should be calculated as an HMAC (Hash-based Message Authentication Code) with &#x60;SHA256&#x60; hash algorithm
/// @param nonce Optional for grant type &#x60;client_signature&#x60;; delivers user generated initialization vector for the server token (optional)
/// @param state Will be passed back in the response (optional)
/// @param scope Describes type of the access for assigned token, possible values: &#x60;connection&#x60;, &#x60;session&#x60;, &#x60;session:name&#x60;, &#x60;trade:[read, read_write, none]&#x60;, &#x60;wallet:[read, read_write, none]&#x60;, &#x60;account:[read, read_write, none]&#x60;, &#x60;expires:NUMBER&#x60; (token will expire after &#x60;NUMBER&#x60; of seconds).&lt;/BR&gt;&lt;/BR&gt; **NOTICE:** Depending on choosing an authentication method (&#x60;&#x60;&#x60;grant type&#x60;&#x60;&#x60;) some scopes could be narrowed by the server. e.g. when &#x60;&#x60;&#x60;grant_type &#x3D; client_credentials&#x60;&#x60;&#x60; and &#x60;&#x60;&#x60;scope &#x3D; wallet:read_write&#x60;&#x60;&#x60; it&#39;s modified by the server as &#x60;&#x60;&#x60;scope &#x3D; wallet:read&#x60;&#x60;&#x60; (optional)
/// 
///  code:200 message:"ok response",
///  code:429 message:"over limit"
///
/// @return NSObject*
-(NSURLSessionTask*) publicAuthGetWithGrantType: (NSString*) grantType
    username: (NSString*) username
    password: (NSString*) password
    clientId: (NSString*) clientId
    clientSecret: (NSString*) clientSecret
    refreshToken: (NSString*) refreshToken
    timestamp: (NSString*) timestamp
    signature: (NSString*) signature
    nonce: (NSString*) nonce
    state: (NSString*) state
    scope: (NSString*) scope
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Stop sending heartbeat messages.
/// 
///
/// 
///  code:200 message:"ok response",
///  code:400 message:"result when used via rest/HTTP"
///
/// @return NSObject*
-(NSURLSessionTask*) publicDisableHeartbeatGetWithCompletionHandler: 
    (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves announcements from the last 30 days.
/// 
///
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetAnnouncementsGetWithCompletionHandler: 
    (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves the summary information such as open interest, 24h volume, etc. for all instruments for the currency (optionally filtered by kind).
/// 
///
/// @param currency The currency symbol
/// @param kind Instrument kind, if not provided instruments of all kinds are considered (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetBookSummaryByCurrencyGetWithCurrency: (NSString*) currency
    kind: (NSString*) kind
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves the summary information such as open interest, 24h volume, etc. for a specific instrument.
/// 
///
/// @param instrumentName Instrument name
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetBookSummaryByInstrumentGetWithInstrumentName: (NSString*) instrumentName
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves contract size of provided instrument.
/// 
///
/// @param instrumentName Instrument name
/// 
///  code:200 message:"ok response"
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetContractSizeGetWithInstrumentName: (NSString*) instrumentName
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves all cryptocurrencies supported by the API.
/// 
///
/// 
///  code:200 message:"ok response"
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetCurrenciesGetWithCompletionHandler: 
    (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieve the latest user trades that have occurred for PERPETUAL instruments in a specific currency symbol and within given time range.
/// 
///
/// @param instrumentName Instrument name
/// @param length Specifies time period. &#x60;8h&#x60; - 8 hours, &#x60;24h&#x60; - 24 hours (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetFundingChartDataGetWithInstrumentName: (NSString*) instrumentName
    length: (NSString*) length
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Provides information about historical volatility for given cryptocurrency.
/// 
///
/// @param currency The currency symbol
/// 
///  code:200 message:"ok response"
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetHistoricalVolatilityGetWithCurrency: (NSString*) currency
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves the current index price for the instruments, for the selected currency.
/// 
///
/// @param currency The currency symbol
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetIndexGetWithCurrency: (NSString*) currency
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves available trading instruments. This method can be used to see which instruments are available for trading, or which instruments have existed historically.
/// 
///
/// @param currency The currency symbol
/// @param kind Instrument kind, if not provided instruments of all kinds are considered (optional)
/// @param expired Set to true to show expired instruments instead of active ones. (optional) (default to @(NO))
/// 
///  code:200 message:"ok response"
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetInstrumentsGetWithCurrency: (NSString*) currency
    kind: (NSString*) kind
    expired: (NSNumber*) expired
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves historical settlement, delivery and bankruptcy events coming from all instruments within given currency.
/// 
///
/// @param currency The currency symbol
/// @param type Settlement type (optional)
/// @param count Number of requested items, default - &#x60;20&#x60; (optional)
/// @param continuation Continuation token for pagination (optional)
/// @param searchStartTimestamp The latest timestamp to return result for (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetLastSettlementsByCurrencyGetWithCurrency: (NSString*) currency
    type: (NSString*) type
    count: (NSNumber*) count
    continuation: (NSString*) continuation
    searchStartTimestamp: (NSNumber*) searchStartTimestamp
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves historical public settlement, delivery and bankruptcy events filtered by instrument name.
/// 
///
/// @param instrumentName Instrument name
/// @param type Settlement type (optional)
/// @param count Number of requested items, default - &#x60;20&#x60; (optional)
/// @param continuation Continuation token for pagination (optional)
/// @param searchStartTimestamp The latest timestamp to return result for (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetLastSettlementsByInstrumentGetWithInstrumentName: (NSString*) instrumentName
    type: (NSString*) type
    count: (NSNumber*) count
    continuation: (NSString*) continuation
    searchStartTimestamp: (NSNumber*) searchStartTimestamp
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieve the latest trades that have occurred for instruments in a specific currency symbol and within given time range.
/// 
///
/// @param currency The currency symbol
/// @param startTimestamp The earliest timestamp to return result for
/// @param endTimestamp The most recent timestamp to return result for
/// @param kind Instrument kind, if not provided instruments of all kinds are considered (optional)
/// @param count Number of requested items, default - &#x60;10&#x60; (optional)
/// @param includeOld Include trades older than 7 days, default - &#x60;false&#x60; (optional)
/// @param sorting Direction of results sorting (&#x60;default&#x60; value means no sorting, results will be returned in order in which they left the database) (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetLastTradesByCurrencyAndTimeGetWithCurrency: (NSString*) currency
    startTimestamp: (NSNumber*) startTimestamp
    endTimestamp: (NSNumber*) endTimestamp
    kind: (NSString*) kind
    count: (NSNumber*) count
    includeOld: (NSNumber*) includeOld
    sorting: (NSString*) sorting
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieve the latest trades that have occurred for instruments in a specific currency symbol.
/// 
///
/// @param currency The currency symbol
/// @param kind Instrument kind, if not provided instruments of all kinds are considered (optional)
/// @param startId The ID number of the first trade to be returned (optional)
/// @param endId The ID number of the last trade to be returned (optional)
/// @param count Number of requested items, default - &#x60;10&#x60; (optional)
/// @param includeOld Include trades older than 7 days, default - &#x60;false&#x60; (optional)
/// @param sorting Direction of results sorting (&#x60;default&#x60; value means no sorting, results will be returned in order in which they left the database) (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetLastTradesByCurrencyGetWithCurrency: (NSString*) currency
    kind: (NSString*) kind
    startId: (NSString*) startId
    endId: (NSString*) endId
    count: (NSNumber*) count
    includeOld: (NSNumber*) includeOld
    sorting: (NSString*) sorting
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieve the latest trades that have occurred for a specific instrument and within given time range.
/// 
///
/// @param instrumentName Instrument name
/// @param startTimestamp The earliest timestamp to return result for
/// @param endTimestamp The most recent timestamp to return result for
/// @param count Number of requested items, default - &#x60;10&#x60; (optional)
/// @param includeOld Include trades older than 7 days, default - &#x60;false&#x60; (optional)
/// @param sorting Direction of results sorting (&#x60;default&#x60; value means no sorting, results will be returned in order in which they left the database) (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetLastTradesByInstrumentAndTimeGetWithInstrumentName: (NSString*) instrumentName
    startTimestamp: (NSNumber*) startTimestamp
    endTimestamp: (NSNumber*) endTimestamp
    count: (NSNumber*) count
    includeOld: (NSNumber*) includeOld
    sorting: (NSString*) sorting
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieve the latest trades that have occurred for a specific instrument.
/// 
///
/// @param instrumentName Instrument name
/// @param startSeq The sequence number of the first trade to be returned (optional)
/// @param endSeq The sequence number of the last trade to be returned (optional)
/// @param count Number of requested items, default - &#x60;10&#x60; (optional)
/// @param includeOld Include trades older than 7 days, default - &#x60;false&#x60; (optional)
/// @param sorting Direction of results sorting (&#x60;default&#x60; value means no sorting, results will be returned in order in which they left the database) (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetLastTradesByInstrumentGetWithInstrumentName: (NSString*) instrumentName
    startSeq: (NSNumber*) startSeq
    endSeq: (NSNumber*) endSeq
    count: (NSNumber*) count
    includeOld: (NSNumber*) includeOld
    sorting: (NSString*) sorting
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves the order book, along with other market values for a given instrument.
/// 
///
/// @param instrumentName The instrument name for which to retrieve the order book, see [&#x60;getinstruments&#x60;](#getinstruments) to obtain instrument names.
/// @param depth The number of entries to return for bids and asks. (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetOrderBookGetWithInstrumentName: (NSString*) instrumentName
    depth: (NSNumber*) depth
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves the current time (in milliseconds). This API endpoint can be used to check the clock skew between your software and Deribit's systems.
/// 
///
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetTimeGetWithCompletionHandler: 
    (void (^)(NSObject* output, NSError* error)) handler;


/// Retrieves aggregated 24h trade volumes for different instrument types and currencies.
/// 
///
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetTradeVolumesGetWithCompletionHandler: 
    (void (^)(NSObject* output, NSError* error)) handler;


/// Publicly available market data used to generate a TradingView candle chart.
/// 
///
/// @param instrumentName Instrument name
/// @param startTimestamp The earliest timestamp to return result for
/// @param endTimestamp The most recent timestamp to return result for
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicGetTradingviewChartDataGetWithInstrumentName: (NSString*) instrumentName
    startTimestamp: (NSNumber*) startTimestamp
    endTimestamp: (NSNumber*) endTimestamp
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Method used to introduce the client software connected to Deribit platform over websocket. Provided data may have an impact on the maintained connection and will be collected for internal statistical purposes. In response, Deribit will also introduce itself.
/// 
///
/// @param clientName Client software name
/// @param clientVersion Client software version
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicHelloGetWithClientName: (NSString*) clientName
    clientVersion: (NSString*) clientVersion
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Signals the Websocket connection to send and request heartbeats. Heartbeats can be used to detect stale connections. When heartbeats have been set up, the API server will send `heartbeat` messages and `test_request` messages. Your software should respond to `test_request` messages by sending a `/api/v2/public/test` request. If your software fails to do so, the API server will immediately close the connection. If your account is configured to cancel on disconnect, any orders opened over the connection will be cancelled.
/// 
///
/// @param interval The heartbeat interval in seconds, but not less than 10
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicSetHeartbeatGetWithInterval: (NSNumber*) interval
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Subscribe to one or more channels.
/// Subscribe to one or more channels.  This is the same method as [/private/subscribe](#private_subscribe), but it can only be used for 'public' channels. 
///
/// @param channels A list of channels to subscribe to.
/// 
///  code:200 message:"ok response",
///  code:401 message:"not authorised"
///
/// @return NSObject*
-(NSURLSessionTask*) publicSubscribeGetWithChannels: (NSArray<NSString*>*) channels
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Tests the connection to the API server, and returns its version. You can use this to make sure the API is reachable, and matches the expected version.
/// 
///
/// @param expectedResult The value \&quot;exception\&quot; will trigger an error response. This may be useful for testing wrapper libraries. (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicTestGetWithExpectedResult: (NSString*) expectedResult
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Get ticker for an instrument.
/// 
///
/// @param instrumentName Instrument name
/// 
///  code:200 message:"ok response"
///
/// @return NSObject*
-(NSURLSessionTask*) publicTickerGetWithInstrumentName: (NSString*) instrumentName
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;


/// Method used to introduce the client software connected to Deribit platform over websocket. Provided data may have an impact on the maintained connection and will be collected for internal statistical purposes. In response, Deribit will also introduce itself.
/// 
///
/// @param field Name of the field to be validated, examples: postal_code, date_of_birth
/// @param value Value to be checked
/// @param value2 Additional value to be compared with (optional)
/// 
///  code:200 message:""
///
/// @return NSObject*
-(NSURLSessionTask*) publicValidateFieldGetWithField: (NSString*) field
    value: (NSString*) value
    value2: (NSString*) value2
    completionHandler: (void (^)(NSObject* output, NSError* error)) handler;



@end
