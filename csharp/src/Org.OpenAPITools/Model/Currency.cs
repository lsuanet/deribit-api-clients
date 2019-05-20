/* 
 * Deribit API
 *
 * #Overview  Deribit provides three different interfaces to access the API:  * [JSON-RPC over Websocket](#json-rpc) * [JSON-RPC over HTTP](#json-rpc) * [FIX](#fix-api) (Financial Information eXchange)  With the API Console you can use and test the JSON-RPC API, both via HTTP and  via Websocket. To visit the API console, go to __Account > API tab >  API Console tab.__   ##Naming Deribit tradeable assets or instruments use the following system of naming:  |Kind|Examples|Template|Comments| |- -- -|- -- -- -- -|- -- -- -- -|- -- -- -- -| |Future|<code>BTC-25MAR16</code>, <code>BTC-5AUG16</code>|<code>BTC-DMMMYY</code>|<code>BTC</code> is currency, <code>DMMMYY</code> is expiration date, <code>D</code> stands for day of month (1 or 2 digits), <code>MMM</code> - month (3 first letters in English), <code>YY</code> stands for year.| |Perpetual|<code>BTC-PERPETUAL</code>                        ||Perpetual contract for currency <code>BTC</code>.| |Option|<code>BTC-25MAR16-420-C</code>, <code>BTC-5AUG16-580-P</code>|<code>BTC-DMMMYY-STRIKE-K</code>|<code>STRIKE</code> is option strike price in USD. Template <code>K</code> is option kind: <code>C</code> for call options or <code>P</code> for put options.|   # JSON-RPC JSON-RPC is a light-weight remote procedure call (RPC) protocol. The  [JSON-RPC specification](https://www.jsonrpc.org/specification) defines the data structures that are used for the messages that are exchanged between client and server, as well as the rules around their processing. JSON-RPC uses JSON (RFC 4627) as data format.  JSON-RPC is transport agnostic: it does not specify which transport mechanism must be used. The Deribit API supports both Websocket (preferred) and HTTP (with limitations: subscriptions are not supported over HTTP).  ## Request messages > An example of a request message:  ```json {     \"jsonrpc\": \"2.0\",     \"id\": 8066,     \"method\": \"public/ticker\",     \"params\": {         \"instrument\": \"BTC-24AUG18-6500-P\"     } } ```  According to the JSON-RPC sepcification the requests must be JSON objects with the following fields.  |Name|Type|Description| |- -- -|- -- -|- -- -- -- -- --| |jsonrpc|string|The version of the JSON-RPC spec: \"2.0\"| |id|integer or string|An identifier of the request. If it is included, then the response will contain the same identifier| |method|string|The method to be invoked| |params|object|The parameters values for the method. The field names must match with the expected parameter names. The parameters that are expected are described in the documentation for the methods, below.|  <aside class=\"warning\"> The JSON-RPC specification describes two features that are currently not supported by the API:  <ul> <li>Specification of parameter values by position</li> <li>Batch requests</li> </ul>  </aside>   ## Response messages > An example of a response message:  ```json {     \"jsonrpc\": \"2.0\",     \"id\": 5239,     \"testnet\": false,     \"result\": [         {             \"currency\": \"BTC\",             \"currencyLong\": \"Bitcoin\",             \"minConfirmation\": 2,             \"txFee\": 0.0006,             \"isActive\": true,             \"coinType\": \"BITCOIN\",             \"baseAddress\": null         }     ],     \"usIn\": 1535043730126248,     \"usOut\": 1535043730126250,     \"usDiff\": 2 } ```  The JSON-RPC API always responds with a JSON object with the following fields.   |Name|Type|Description| |- -- -|- -- -|- -- -- -- -- --| |id|integer|This is the same id that was sent in the request.| |result|any|If successful, the result of the API call. The format for the result is described with each method.| |error|error object|Only present if there was an error invoking the method. The error object is described below.| |testnet|boolean|Indicates whether the API in use is actually the test API.  <code>false</code> for production server, <code>true</code> for test server.| |usIn|integer|The timestamp when the requests was received (microseconds since the Unix epoch)| |usOut|integer|The timestamp when the response was sent (microseconds since the Unix epoch)| |usDiff|integer|The number of microseconds that was spent handling the request|  <aside class=\"notice\"> The fields <code>testnet</code>, <code>usIn</code>, <code>usOut</code> and <code>usDiff</code> are not part of the JSON-RPC standard.  <p>In order not to clutter the examples they will generally be omitted from the example code.</p> </aside>  > An example of a response with an error:  ```json {     \"jsonrpc\": \"2.0\",     \"id\": 8163,     \"error\": {         \"code\": 11050,         \"message\": \"bad_request\"     },     \"testnet\": false,     \"usIn\": 1535037392434763,     \"usOut\": 1535037392448119,     \"usDiff\": 13356 } ``` In case of an error the response message will contain the error field, with as value an object with the following with the following fields:  |Name|Type|Description |- -- -|- -- -|- -- -- -- -- --| |code|integer|A number that indicates the kind of error.| |message|string|A short description that indicates the kind of error.| |data|any|Additional data about the error. This field may be omitted.|  ## Notifications  > An example of a notification:  ```json {     \"jsonrpc\": \"2.0\",     \"method\": \"subscription\",     \"params\": {         \"channel\": \"deribit_price_index.btc_usd\",         \"data\": {             \"timestamp\": 1535098298227,             \"price\": 6521.17,             \"index_name\": \"btc_usd\"         }     } } ```  API users can subscribe to certain types of notifications. This means that they will receive JSON-RPC notification-messages from the server when certain events occur, such as changes to the index price or changes to the order book for a certain instrument.   The API methods [public/subscribe](#public-subscribe) and [private/subscribe](#private-subscribe) are used to set up a subscription. Since HTTP does not support the sending of messages from server to client, these methods are only availble when using the Websocket transport mechanism.  At the moment of subscription a \"channel\" must be specified. The channel determines the type of events that will be received.  See [Subscriptions](#subscriptions) for more details about the channels.  In accordance with the JSON-RPC specification, the format of a notification  is that of a request message without an <code>id</code> field. The value of the <code>method</code> field will always be <code>\"subscription\"</code>. The <code>params</code> field will always be an object with 2 members: <code>channel</code> and <code>data</code>. The value of the <code>channel</code> member is the name of the channel (a string). The value of the <code>data</code> member is an object that contains data  that is specific for the channel.   ## Authentication  > An example of a JSON request with token:  ```json {     \"id\": 5647,     \"method\": \"private/get_subaccounts\",     \"params\": {         \"access_token\": \"67SVutDoVZSzkUStHSuk51WntMNBJ5mh5DYZhwzpiqDF\"     } } ```  The API consists of `public` and `private` methods. The public methods do not require authentication. The private methods use OAuth 2.0 authentication. This means that a valid OAuth access token must be included in the request, which can get achived by calling method [public/auth](#public-auth).  When the token was assigned to the user, it should be passed along, with other request parameters, back to the server:  |Connection type|Access token placement |- -- -|- -- -- -- -- --| |**Websocket**|Inside request JSON parameters, as an `access_token` field| |**HTTP (REST)**|Header `Authorization: bearer ```Token``` ` value|  ### Additional authorization method - basic user credentials  <span style=\"color:red\"><b> ! Not recommended - however, it could be useful for quick testing API</b></span></br>  Every `private` method could be accessed by providing, inside HTTP `Authorization: Basic XXX` header, values with user `ClientId` and assigned `ClientSecret` (both values can be found on the API page on the Deribit website) encoded with `Base64`:  <code>Authorization: Basic BASE64(`ClientId` + `:` + `ClientSecret`)</code>   ### Additional authorization method - Deribit signature credentials  The Derbit service provides dedicated authorization method, which harness user generated signature to increase security level for passing request data. Generated value is passed inside `Authorization` header, coded as:  <code>Authorization: deri-hmac-sha256 id=```ClientId```,ts=```Timestamp```,sig=```Signature```,nonce=```Nonce```</code>  where:  |Deribit credential|Description |- -- -|- -- -- -- -- --| |*ClientId*|Can be found on the API page on the Deribit website| |*Timestamp*|Time when the request was generated - given as **miliseconds**. It's valid for **60 seconds** since generation, after that time any request with an old timestamp will be rejected.| |*Signature*|Value for signature calculated as described below | |*Nonce*|Single usage, user generated initialization vector for the server token|  The signature is generated by the following formula:  <code> Signature = HEX_STRING( HMAC-SHA256( ClientSecret, StringToSign ) );</code></br>  <code> StringToSign =  Timestamp + \"\\n\" + Nonce + \"\\n\" + RequestData;</code></br>  <code> RequestData =  UPPERCASE(HTTP_METHOD())  + \"\\n\" + URI() + \"\\n\" + RequestBody + \"\\n\";</code></br>   e.g. (using shell with ```openssl``` tool):  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientId=AAAAAAAAAAA</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientSecret=ABCD</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Timestamp=$( date +%s000 )</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Nonce=$( cat /dev/urandom | tr -dc 'a-z0-9' | head -c8 )</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;URI=\"/api/v2/private/get_account_summary?currency=BTC\"</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;HttpMethod=GET</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Body=\"\"</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Signature=$( echo -ne \"${Timestamp}\\n${Nonce}\\n${HttpMethod}\\n${URI}\\n${Body}\\n\" | openssl sha256 -r -hmac \"$ClientSecret\" | cut -f1 -d' ' )</code></br></br> <code>&nbsp;&nbsp;&nbsp;&nbsp;echo $Signature</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;shell output> ea40d5e5e4fae235ab22b61da98121fbf4acdc06db03d632e23c66bcccb90d2c  (**WARNING**: Exact value depends on current timestamp and client credentials</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;curl -s -X ${HttpMethod} -H \"Authorization: deri-hmac-sha256 id=${ClientId},ts=${Timestamp},nonce=${Nonce},sig=${Signature}\" \"https://www.deribit.com${URI}\"</code></br></br>    ### Additional authorization method - signature credentials (WebSocket API)  When connecting through Websocket, user can request for authorization using ```client_credential``` method, which requires providing following parameters (as a part of JSON request):  |JSON parameter|Description |- -- -|- -- -- -- -- --| |*grant_type*|Must be **client_signature**| |*client_id*|Can be found on the API page on the Deribit website| |*timestamp*|Time when the request was generated - given as **miliseconds**. It's valid for **60 seconds** since generation, after that time any request with an old timestamp will be rejected.| |*signature*|Value for signature calculated as described below | |*nonce*|Single usage, user generated initialization vector for the server token| |*data*|**Optional** field, which contains any user specific value|  The signature is generated by the following formula:  <code> StringToSign =  Timestamp + \"\\n\" + Nonce + \"\\n\" + Data;</code></br>  <code> Signature = HEX_STRING( HMAC-SHA256( ClientSecret, StringToSign ) );</code></br>   e.g. (using shell with ```openssl``` tool):  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientId=AAAAAAAAAAA</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;ClientSecret=ABCD</code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Timestamp=$( date +%s000 ) # e.g. 1554883365000 </code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Nonce=$( cat /dev/urandom | tr -dc 'a-z0-9' | head -c8 ) # e.g. fdbmmz79 </code></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Data=\"\"</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;Signature=$( echo -ne \"${Timestamp}\\n${Nonce}\\n${Data}\\n\" | openssl sha256 -r -hmac \"$ClientSecret\" | cut -f1 -d' ' )</code></br></br> <code>&nbsp;&nbsp;&nbsp;&nbsp;echo $Signature</code></br></br>  <code>&nbsp;&nbsp;&nbsp;&nbsp;shell output> e20c9cd5639d41f8bbc88f4d699c4baf94a4f0ee320e9a116b72743c449eb994  (**WARNING**: Exact value depends on current timestamp and client credentials</code></br></br>   You can also check the signature value using some online tools like, e.g: [https://codebeautify.org/hmac-generator](https://codebeautify.org/hmac-generator) (but don't forget about adding *newline* after each part of the hashed text and remember that you **should use** it only with your **test credentials**).   Here's a sample JSON request created using the values from the example above:  <code> {                            </br> &nbsp;&nbsp;\"jsonrpc\" : \"2.0\",         </br> &nbsp;&nbsp;\"id\" : 9929,               </br> &nbsp;&nbsp;\"method\" : \"public/auth\",  </br> &nbsp;&nbsp;\"params\" :                 </br> &nbsp;&nbsp;{                        </br> &nbsp;&nbsp;&nbsp;&nbsp;\"grant_type\" : \"client_signature\",   </br> &nbsp;&nbsp;&nbsp;&nbsp;\"client_id\" : \"AAAAAAAAAAA\",         </br> &nbsp;&nbsp;&nbsp;&nbsp;\"timestamp\": \"1554883365000\",        </br> &nbsp;&nbsp;&nbsp;&nbsp;\"nonce\": \"fdbmmz79\",                 </br> &nbsp;&nbsp;&nbsp;&nbsp;\"data\": \"\",                          </br> &nbsp;&nbsp;&nbsp;&nbsp;\"signature\" : \"e20c9cd5639d41f8bbc88f4d699c4baf94a4f0ee320e9a116b72743c449eb994\"  </br> &nbsp;&nbsp;}                        </br> }                            </br> </code>   ### Access scope  When asking for `access token` user can provide the required access level (called `scope`) which defines what type of functionality he/she wants to use, and whether requests are only going to check for some data or also to update them.  Scopes are required and checked for `private` methods, so if you plan to use only `public` information you can stay with values assigned by default.  |Scope|Description |- -- -|- -- -- -- -- --| |*account:read*|Access to **account** methods - read only data| |*account:read_write*|Access to **account** methods - allows to manage account settings, add subaccounts, etc.| |*trade:read*|Access to **trade** methods - read only data| |*trade:read_write*|Access to **trade** methods - required to create and modify orders| |*wallet:read*|Access to **wallet** methods - read only data| |*wallet:read_write*|Access to **wallet** methods - allows to withdraw, generate new deposit address, etc.| |*wallet:none*, *account:none*, *trade:none*|Blocked access to specified functionality|    <span style=\"color:red\">**NOTICE:**</span> Depending on choosing an authentication method (```grant type```) some scopes could be narrowed by the server. e.g. when ```grant_type = client_credentials``` and ```scope = wallet:read_write``` it's modified by the server as ```scope = wallet:read```\"   ## JSON-RPC over websocket Websocket is the prefered transport mechanism for the JSON-RPC API, because it is faster and because it can support [subscriptions](#subscriptions) and [cancel on disconnect](#private-enable_cancel_on_disconnect). The code examples that can be found next to each of the methods show how websockets can be used from Python or Javascript/node.js.  ## JSON-RPC over HTTP Besides websockets it is also possible to use the API via HTTP. The code examples for 'shell' show how this can be done using curl. Note that subscriptions and cancel on disconnect are not supported via HTTP.  #Methods 
 *
 * OpenAPI spec version: 2.0.0
 * 
 * Generated by: https://github.com/openapitools/openapi-generator.git
 */

using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.ComponentModel.DataAnnotations;
using OpenAPIDateConverter = Org.OpenAPITools.Client.OpenAPIDateConverter;

namespace Org.OpenAPITools.Model
{
    /// <summary>
    /// Currency
    /// </summary>
    [DataContract]
    public partial class Currency :  IEquatable<Currency>, IValidatableObject
    {
        /// <summary>
        /// The type of the currency.
        /// </summary>
        /// <value>The type of the currency.</value>
        [JsonConverter(typeof(StringEnumConverter))]
        public enum CoinTypeEnum
        {
            /// <summary>
            /// Enum BITCOIN for value: BITCOIN
            /// </summary>
            [EnumMember(Value = "BITCOIN")]
            BITCOIN = 1,

            /// <summary>
            /// Enum ETHER for value: ETHER
            /// </summary>
            [EnumMember(Value = "ETHER")]
            ETHER = 2

        }

        /// <summary>
        /// The type of the currency.
        /// </summary>
        /// <value>The type of the currency.</value>
        [DataMember(Name="coin_type", EmitDefaultValue=false)]
        public CoinTypeEnum CoinType { get; set; }
        /// <summary>
        /// Initializes a new instance of the <see cref="Currency" /> class.
        /// </summary>
        [JsonConstructorAttribute]
        protected Currency() { }
        /// <summary>
        /// Initializes a new instance of the <see cref="Currency" /> class.
        /// </summary>
        /// <param name="minConfirmations">Minimum number of block chain confirmations before deposit is accepted..</param>
        /// <param name="minWithdrawalFee">The minimum transaction fee paid for withdrawals.</param>
        /// <param name="disabledDepositAddressCreation">False if deposit address creation is disabled.</param>
        /// <param name="currency">The abbreviation of the currency. This abbreviation is used elsewhere in the API to identify the currency. (required).</param>
        /// <param name="currencyLong">The full name for the currency. (required).</param>
        /// <param name="withdrawalFee">The total transaction fee paid for withdrawals (required).</param>
        /// <param name="feePrecision">fee precision.</param>
        /// <param name="withdrawalPriorities">withdrawalPriorities.</param>
        /// <param name="coinType">The type of the currency. (required).</param>
        public Currency(int? minConfirmations = default(int?), decimal? minWithdrawalFee = default(decimal?), bool? disabledDepositAddressCreation = default(bool?), string currency = default(string), string currencyLong = default(string), decimal? withdrawalFee = default(decimal?), int? feePrecision = default(int?), List<CurrencyWithdrawalPriorities> withdrawalPriorities = default(List<CurrencyWithdrawalPriorities>), CoinTypeEnum coinType = default(CoinTypeEnum))
        {
            // to ensure "currency" is required (not null)
            if (currency == null)
            {
                throw new InvalidDataException("currency is a required property for Currency and cannot be null");
            }
            else
            {
                this._Currency = currency;
            }
            
            // to ensure "currencyLong" is required (not null)
            if (currencyLong == null)
            {
                throw new InvalidDataException("currencyLong is a required property for Currency and cannot be null");
            }
            else
            {
                this.CurrencyLong = currencyLong;
            }
            
            // to ensure "withdrawalFee" is required (not null)
            if (withdrawalFee == null)
            {
                throw new InvalidDataException("withdrawalFee is a required property for Currency and cannot be null");
            }
            else
            {
                this.WithdrawalFee = withdrawalFee;
            }
            
            // to ensure "coinType" is required (not null)
            if (coinType == null)
            {
                throw new InvalidDataException("coinType is a required property for Currency and cannot be null");
            }
            else
            {
                this.CoinType = coinType;
            }
            
            this.MinConfirmations = minConfirmations;
            this.MinWithdrawalFee = minWithdrawalFee;
            this.DisabledDepositAddressCreation = disabledDepositAddressCreation;
            this.FeePrecision = feePrecision;
            this.WithdrawalPriorities = withdrawalPriorities;
        }
        
        /// <summary>
        /// Minimum number of block chain confirmations before deposit is accepted.
        /// </summary>
        /// <value>Minimum number of block chain confirmations before deposit is accepted.</value>
        [DataMember(Name="min_confirmations", EmitDefaultValue=false)]
        public int? MinConfirmations { get; set; }

        /// <summary>
        /// The minimum transaction fee paid for withdrawals
        /// </summary>
        /// <value>The minimum transaction fee paid for withdrawals</value>
        [DataMember(Name="min_withdrawal_fee", EmitDefaultValue=false)]
        public decimal? MinWithdrawalFee { get; set; }

        /// <summary>
        /// False if deposit address creation is disabled
        /// </summary>
        /// <value>False if deposit address creation is disabled</value>
        [DataMember(Name="disabled_deposit_address_creation", EmitDefaultValue=false)]
        public bool? DisabledDepositAddressCreation { get; set; }

        /// <summary>
        /// The abbreviation of the currency. This abbreviation is used elsewhere in the API to identify the currency.
        /// </summary>
        /// <value>The abbreviation of the currency. This abbreviation is used elsewhere in the API to identify the currency.</value>
        [DataMember(Name="currency", EmitDefaultValue=false)]
        public string _Currency { get; set; }

        /// <summary>
        /// The full name for the currency.
        /// </summary>
        /// <value>The full name for the currency.</value>
        [DataMember(Name="currency_long", EmitDefaultValue=false)]
        public string CurrencyLong { get; set; }

        /// <summary>
        /// The total transaction fee paid for withdrawals
        /// </summary>
        /// <value>The total transaction fee paid for withdrawals</value>
        [DataMember(Name="withdrawal_fee", EmitDefaultValue=false)]
        public decimal? WithdrawalFee { get; set; }

        /// <summary>
        /// fee precision
        /// </summary>
        /// <value>fee precision</value>
        [DataMember(Name="fee_precision", EmitDefaultValue=false)]
        public int? FeePrecision { get; set; }

        /// <summary>
        /// Gets or Sets WithdrawalPriorities
        /// </summary>
        [DataMember(Name="withdrawal_priorities", EmitDefaultValue=false)]
        public List<CurrencyWithdrawalPriorities> WithdrawalPriorities { get; set; }


        /// <summary>
        /// Returns the string presentation of the object
        /// </summary>
        /// <returns>String presentation of the object</returns>
        public override string ToString()
        {
            var sb = new StringBuilder();
            sb.Append("class Currency {\n");
            sb.Append("  MinConfirmations: ").Append(MinConfirmations).Append("\n");
            sb.Append("  MinWithdrawalFee: ").Append(MinWithdrawalFee).Append("\n");
            sb.Append("  DisabledDepositAddressCreation: ").Append(DisabledDepositAddressCreation).Append("\n");
            sb.Append("  _Currency: ").Append(_Currency).Append("\n");
            sb.Append("  CurrencyLong: ").Append(CurrencyLong).Append("\n");
            sb.Append("  WithdrawalFee: ").Append(WithdrawalFee).Append("\n");
            sb.Append("  FeePrecision: ").Append(FeePrecision).Append("\n");
            sb.Append("  WithdrawalPriorities: ").Append(WithdrawalPriorities).Append("\n");
            sb.Append("  CoinType: ").Append(CoinType).Append("\n");
            sb.Append("}\n");
            return sb.ToString();
        }
  
        /// <summary>
        /// Returns the JSON string presentation of the object
        /// </summary>
        /// <returns>JSON string presentation of the object</returns>
        public virtual string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }

        /// <summary>
        /// Returns true if objects are equal
        /// </summary>
        /// <param name="input">Object to be compared</param>
        /// <returns>Boolean</returns>
        public override bool Equals(object input)
        {
            return this.Equals(input as Currency);
        }

        /// <summary>
        /// Returns true if Currency instances are equal
        /// </summary>
        /// <param name="input">Instance of Currency to be compared</param>
        /// <returns>Boolean</returns>
        public bool Equals(Currency input)
        {
            if (input == null)
                return false;

            return 
                (
                    this.MinConfirmations == input.MinConfirmations ||
                    (this.MinConfirmations != null &&
                    this.MinConfirmations.Equals(input.MinConfirmations))
                ) && 
                (
                    this.MinWithdrawalFee == input.MinWithdrawalFee ||
                    (this.MinWithdrawalFee != null &&
                    this.MinWithdrawalFee.Equals(input.MinWithdrawalFee))
                ) && 
                (
                    this.DisabledDepositAddressCreation == input.DisabledDepositAddressCreation ||
                    (this.DisabledDepositAddressCreation != null &&
                    this.DisabledDepositAddressCreation.Equals(input.DisabledDepositAddressCreation))
                ) && 
                (
                    this._Currency == input._Currency ||
                    (this._Currency != null &&
                    this._Currency.Equals(input._Currency))
                ) && 
                (
                    this.CurrencyLong == input.CurrencyLong ||
                    (this.CurrencyLong != null &&
                    this.CurrencyLong.Equals(input.CurrencyLong))
                ) && 
                (
                    this.WithdrawalFee == input.WithdrawalFee ||
                    (this.WithdrawalFee != null &&
                    this.WithdrawalFee.Equals(input.WithdrawalFee))
                ) && 
                (
                    this.FeePrecision == input.FeePrecision ||
                    (this.FeePrecision != null &&
                    this.FeePrecision.Equals(input.FeePrecision))
                ) && 
                (
                    this.WithdrawalPriorities == input.WithdrawalPriorities ||
                    this.WithdrawalPriorities != null &&
                    input.WithdrawalPriorities != null &&
                    this.WithdrawalPriorities.SequenceEqual(input.WithdrawalPriorities)
                ) && 
                (
                    this.CoinType == input.CoinType ||
                    (this.CoinType != null &&
                    this.CoinType.Equals(input.CoinType))
                );
        }

        /// <summary>
        /// Gets the hash code
        /// </summary>
        /// <returns>Hash code</returns>
        public override int GetHashCode()
        {
            unchecked // Overflow is fine, just wrap
            {
                int hashCode = 41;
                if (this.MinConfirmations != null)
                    hashCode = hashCode * 59 + this.MinConfirmations.GetHashCode();
                if (this.MinWithdrawalFee != null)
                    hashCode = hashCode * 59 + this.MinWithdrawalFee.GetHashCode();
                if (this.DisabledDepositAddressCreation != null)
                    hashCode = hashCode * 59 + this.DisabledDepositAddressCreation.GetHashCode();
                if (this._Currency != null)
                    hashCode = hashCode * 59 + this._Currency.GetHashCode();
                if (this.CurrencyLong != null)
                    hashCode = hashCode * 59 + this.CurrencyLong.GetHashCode();
                if (this.WithdrawalFee != null)
                    hashCode = hashCode * 59 + this.WithdrawalFee.GetHashCode();
                if (this.FeePrecision != null)
                    hashCode = hashCode * 59 + this.FeePrecision.GetHashCode();
                if (this.WithdrawalPriorities != null)
                    hashCode = hashCode * 59 + this.WithdrawalPriorities.GetHashCode();
                if (this.CoinType != null)
                    hashCode = hashCode * 59 + this.CoinType.GetHashCode();
                return hashCode;
            }
        }

        /// <summary>
        /// To validate all properties of the instance
        /// </summary>
        /// <param name="validationContext">Validation context</param>
        /// <returns>Validation Result</returns>
        IEnumerable<System.ComponentModel.DataAnnotations.ValidationResult> IValidatableObject.Validate(ValidationContext validationContext)
        {
            yield break;
        }
    }

}
