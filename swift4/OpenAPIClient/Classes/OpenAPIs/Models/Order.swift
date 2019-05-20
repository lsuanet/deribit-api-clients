//
// Order.swift
//
// Generated by openapi-generator
// https://openapi-generator.tech
//

import Foundation



public struct Order: Codable {

    public enum Direction: String, Codable {
        case buy = "buy"
        case sell = "sell"
    }
    public enum TimeInForce: String, Codable {
        case goodTilCancelled = "good_til_cancelled"
        case fillOrKill = "fill_or_kill"
        case immediateOrCancel = "immediate_or_cancel"
    }
    public enum OrderState: String, Codable {
        case _open = "open"
        case filled = "filled"
        case rejected = "rejected"
        case cancelled = "cancelled"
        case untriggered = "untriggered"
        case triggered = "triggered"
    }
    public enum Advanced: String, Codable {
        case usd = "usd"
        case implv = "implv"
    }
    public enum OrderType: String, Codable {
        case market = "market"
        case limit = "limit"
        case stopMarket = "stop_market"
        case stopLimit = "stop_limit"
    }
    public enum OriginalOrderType: String, Codable {
        case market = "market"
    }
    public enum Trigger: String, Codable {
        case indexPrice = "index_price"
        case markPrice = "mark_price"
        case lastPrice = "last_price"
    }
    /** direction, &#x60;buy&#x60; or &#x60;sell&#x60; */
    public var direction: Direction
    /** &#x60;true&#x60; for reduce-only orders only */
    public var reduceOnly: Bool?
    /** Whether the stop order has been triggered (Only for stop orders) */
    public var triggered: Bool?
    /** Unique order identifier */
    public var orderId: String
    /** Price in base currency */
    public var price: Double
    /** Order time in force: &#x60;\&quot;good_til_cancelled\&quot;&#x60;, &#x60;\&quot;fill_or_kill\&quot;&#x60;, &#x60;\&quot;immediate_or_cancel\&quot;&#x60; */
    public var timeInForce: TimeInForce
    /** &#x60;true&#x60; if created with API */
    public var api: Bool
    /** order state, &#x60;\&quot;open\&quot;&#x60;, &#x60;\&quot;filled\&quot;&#x60;, &#x60;\&quot;rejected\&quot;&#x60;, &#x60;\&quot;cancelled\&quot;&#x60;, &#x60;\&quot;untriggered\&quot;&#x60; */
    public var orderState: OrderState
    /** Implied volatility in percent. (Only if &#x60;advanced&#x3D;\&quot;implv\&quot;&#x60;) */
    public var implv: Double?
    /** advanced type: &#x60;\&quot;usd\&quot;&#x60; or &#x60;\&quot;implv\&quot;&#x60; (Only for options; field is omitted if not applicable).  */
    public var advanced: Advanced?
    /** &#x60;true&#x60; for post-only orders only */
    public var postOnly: Bool
    /** Option price in USD (Only if &#x60;advanced&#x3D;\&quot;usd\&quot;&#x60;) */
    public var usd: Double?
    /** stop price (Only for future stop orders) */
    public var stopPrice: Double?
    /** order type, &#x60;\&quot;limit\&quot;&#x60;, &#x60;\&quot;market\&quot;&#x60;, &#x60;\&quot;stop_limit\&quot;&#x60;, &#x60;\&quot;stop_market\&quot;&#x60; */
    public var orderType: OrderType
    /** The timestamp (seconds since the Unix epoch, with millisecond precision) */
    public var lastUpdateTimestamp: Int
    /** Original order type. Optional field */
    public var originalOrderType: OriginalOrderType?
    /** Maximum amount within an order to be shown to other traders, 0 for invisible order. */
    public var maxShow: Double
    /** Profit and loss in base currency. */
    public var profitLoss: Double?
    /** &#x60;true&#x60; if order was automatically created during liquidation */
    public var isLiquidation: Bool
    /** Filled amount of the order. For perpetual and futures the filled_amount is in USD units, for options - in units or corresponding cryptocurrency contracts, e.g., BTC or ETH. */
    public var filledAmount: Double?
    /** user defined label (up to 32 characters) */
    public var label: String
    /** Commission paid so far (in base currency) */
    public var commission: Double?
    /** It represents the requested order size. For perpetual and futures the amount is in USD units, for options it is amount of corresponding cryptocurrency contracts, e.g., BTC or ETH. */
    public var amount: Double?
    /** Trigger type (Only for stop orders). Allowed values: &#x60;\&quot;index_price\&quot;&#x60;, &#x60;\&quot;mark_price\&quot;&#x60;, &#x60;\&quot;last_price\&quot;&#x60;. */
    public var trigger: Trigger?
    /** Unique instrument identifier */
    public var instrumentName: String?
    /** The timestamp (seconds since the Unix epoch, with millisecond precision) */
    public var creationTimestamp: Int
    /** Average fill price of the order */
    public var averagePrice: Double?

    public init(direction: Direction, reduceOnly: Bool?, triggered: Bool?, orderId: String, price: Double, timeInForce: TimeInForce, api: Bool, orderState: OrderState, implv: Double?, advanced: Advanced?, postOnly: Bool, usd: Double?, stopPrice: Double?, orderType: OrderType, lastUpdateTimestamp: Int, originalOrderType: OriginalOrderType?, maxShow: Double, profitLoss: Double?, isLiquidation: Bool, filledAmount: Double?, label: String, commission: Double?, amount: Double?, trigger: Trigger?, instrumentName: String?, creationTimestamp: Int, averagePrice: Double?) {
        self.direction = direction
        self.reduceOnly = reduceOnly
        self.triggered = triggered
        self.orderId = orderId
        self.price = price
        self.timeInForce = timeInForce
        self.api = api
        self.orderState = orderState
        self.implv = implv
        self.advanced = advanced
        self.postOnly = postOnly
        self.usd = usd
        self.stopPrice = stopPrice
        self.orderType = orderType
        self.lastUpdateTimestamp = lastUpdateTimestamp
        self.originalOrderType = originalOrderType
        self.maxShow = maxShow
        self.profitLoss = profitLoss
        self.isLiquidation = isLiquidation
        self.filledAmount = filledAmount
        self.label = label
        self.commission = commission
        self.amount = amount
        self.trigger = trigger
        self.instrumentName = instrumentName
        self.creationTimestamp = creationTimestamp
        self.averagePrice = averagePrice
    }

    public enum CodingKeys: String, CodingKey { 
        case direction
        case reduceOnly = "reduce_only"
        case triggered
        case orderId = "order_id"
        case price
        case timeInForce = "time_in_force"
        case api
        case orderState = "order_state"
        case implv
        case advanced
        case postOnly = "post_only"
        case usd
        case stopPrice = "stop_price"
        case orderType = "order_type"
        case lastUpdateTimestamp = "last_update_timestamp"
        case originalOrderType = "original_order_type"
        case maxShow = "max_show"
        case profitLoss = "profit_loss"
        case isLiquidation = "is_liquidation"
        case filledAmount = "filled_amount"
        case label
        case commission
        case amount
        case trigger
        case instrumentName = "instrument_name"
        case creationTimestamp = "creation_timestamp"
        case averagePrice = "average_price"
    }


}

