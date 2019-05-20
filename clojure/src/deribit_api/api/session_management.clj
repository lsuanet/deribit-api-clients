(ns deribit-api.api.session-management
  (:require [deribit-api.core :refer [call-api check-required-params with-collection-format *api-context*]]
            [clojure.spec.alpha :as s]
            [spec-tools.core :as st]
            [orchestra.core :refer [defn-spec]]
            [deribit-api.specs.public-trade :refer :all]
            [deribit-api.specs.currency-withdrawal-priorities :refer :all]
            [deribit-api.specs.address-book-item :refer :all]
            [deribit-api.specs.types :refer :all]
            [deribit-api.specs.transfer-item :refer :all]
            [deribit-api.specs.order-id-initial-margin-pair :refer :all]
            [deribit-api.specs.key-number-pair :refer :all]
            [deribit-api.specs.trades-volumes :refer :all]
            [deribit-api.specs.instrument :refer :all]
            [deribit-api.specs.withdrawal :refer :all]
            [deribit-api.specs.portfolio-eth :refer :all]
            [deribit-api.specs.settlement :refer :all]
            [deribit-api.specs.user-trade :refer :all]
            [deribit-api.specs.portfolio :refer :all]
            [deribit-api.specs.currency-portfolio :refer :all]
            [deribit-api.specs.deposit :refer :all]
            [deribit-api.specs.book-summary :refer :all]
            [deribit-api.specs.currency :refer :all]
            [deribit-api.specs.position :refer :all]
            [deribit-api.specs.order :refer :all]
            )
  (:import (java.io File)))


(defn-spec private-disable-cancel-on-disconnect-get-with-http-info any?
  "Disable Cancel On Disconnect for the connection. This does not change the default account setting."
  []
  (call-api "/private/disable_cancel_on_disconnect" :get
            {:path-params   {}
             :header-params {}
             :query-params  {}
             :form-params   {}
             :content-types []
             :accepts       ["application/json"]
             :auth-names    ["bearerAuth"]}))

(defn-spec private-disable-cancel-on-disconnect-get any?
  "Disable Cancel On Disconnect for the connection. This does not change the default account setting."
  []
  (let [res (:data (private-disable-cancel-on-disconnect-get-with-http-info))]
    (if (:decode-models *api-context*)
       (st/decode any? res st/string-transformer)
       res)))


(defn-spec private-enable-cancel-on-disconnect-get-with-http-info any?
  "Enable Cancel On Disconnect for the connection. This does not change the default account setting."
  []
  (call-api "/private/enable_cancel_on_disconnect" :get
            {:path-params   {}
             :header-params {}
             :query-params  {}
             :form-params   {}
             :content-types []
             :accepts       ["application/json"]
             :auth-names    ["bearerAuth"]}))

(defn-spec private-enable-cancel-on-disconnect-get any?
  "Enable Cancel On Disconnect for the connection. This does not change the default account setting."
  []
  (let [res (:data (private-enable-cancel-on-disconnect-get-with-http-info))]
    (if (:decode-models *api-context*)
       (st/decode any? res st/string-transformer)
       res)))


(defn-spec public-disable-heartbeat-get-with-http-info any?
  "Stop sending heartbeat messages."
  []
  (call-api "/public/disable_heartbeat" :get
            {:path-params   {}
             :header-params {}
             :query-params  {}
             :form-params   {}
             :content-types []
             :accepts       ["application/json"]
             :auth-names    ["bearerAuth"]}))

(defn-spec public-disable-heartbeat-get any?
  "Stop sending heartbeat messages."
  []
  (let [res (:data (public-disable-heartbeat-get-with-http-info))]
    (if (:decode-models *api-context*)
       (st/decode any? res st/string-transformer)
       res)))


(defn-spec public-set-heartbeat-get-with-http-info any?
  "Signals the Websocket connection to send and request heartbeats. Heartbeats can be used to detect stale connections.
When heartbeats have been set up, the API server will send `heartbeat` messages and `test_request` messages. Your software should respond to `test_request` messages by sending a `/api/v2/public/test` request. If your software fails to do so, the API server will immediately close the connection. If your account is configured to cancel on disconnect, any orders opened over the connection will be cancelled."
  [interval float?]
  (check-required-params interval)
  (call-api "/public/set_heartbeat" :get
            {:path-params   {}
             :header-params {}
             :query-params  {"interval" interval }
             :form-params   {}
             :content-types []
             :accepts       ["application/json"]
             :auth-names    ["bearerAuth"]}))

(defn-spec public-set-heartbeat-get any?
  "Signals the Websocket connection to send and request heartbeats. Heartbeats can be used to detect stale connections.
When heartbeats have been set up, the API server will send `heartbeat` messages and `test_request` messages. Your software should respond to `test_request` messages by sending a `/api/v2/public/test` request. If your software fails to do so, the API server will immediately close the connection. If your account is configured to cancel on disconnect, any orders opened over the connection will be cancelled."
  [interval float?]
  (let [res (:data (public-set-heartbeat-get-with-http-info interval))]
    (if (:decode-models *api-context*)
       (st/decode any? res st/string-transformer)
       res)))


