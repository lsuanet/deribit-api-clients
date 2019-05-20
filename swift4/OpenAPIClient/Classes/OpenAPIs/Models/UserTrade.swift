//
// UserTrade.swift
//
// Generated by openapi-generator
// https://openapi-generator.tech
//

import Foundation



public struct UserTrade: Codable {

    public enum Direction: String, Codable {
        case buy = "buy"
        case sell = "sell"
    }
    public enum FeeCurrency: String, Codable {
        case btc = "BTC"
        case eth = "ETH"
    }
    public enum OrderType: String, Codable {
        case limit = "limit"
        case market = "market"
        case liquidation = "liquidation"
    }
    public enum State: String, Codable {
        case _open = "open"
        case filled = "filled"
        case rejected = "rejected"
        case cancelled = "cancelled"
        case untriggered = "untriggered"
        case archive = "archive"
    }
    public enum TickDirection: Int, Codable {
        case _0 = 0
        case _1 = 1
        case _2 = 2
        case _3 = 3
    }
    public enum Liquidity: String, Codable {
        case m = "M"
        case t = "T"
    }
    /** Trade direction of the taker */
    public var direction: Direction
    /** Currency, i.e &#x60;\&quot;BTC\&quot;&#x60;, &#x60;\&quot;ETH\&quot;&#x60; */
    public var feeCurrency: FeeCurrency
    /** Id of the user order (maker or taker), i.e. subscriber&#39;s order id that took part in the trade */
    public var orderId: String
    /** The timestamp of the trade */
    public var timestamp: Int
    /** The price of the trade */
    public var price: Double
    /** Option implied volatility for the price (Option only) */
    public var iv: Double?
    /** Unique (per currency) trade identifier */
    public var tradeId: String
    /** User&#39;s fee in units of the specified &#x60;fee_currency&#x60; */
    public var fee: Double
    /** Order type: &#x60;\&quot;limit&#x60;, &#x60;\&quot;market\&quot;&#x60;, or &#x60;\&quot;liquidation\&quot;&#x60; */
    public var orderType: OrderType?
    /** The sequence number of the trade within instrument */
    public var tradeSeq: Int
    /** &#x60;true&#x60; if the trade is against own order. This can only happen when your account has self-trading enabled. Contact an administrator if you think you need that */
    public var selfTrade: Bool
    /** order state, &#x60;\&quot;open\&quot;&#x60;, &#x60;\&quot;filled\&quot;&#x60;, &#x60;\&quot;rejected\&quot;&#x60;, &#x60;\&quot;cancelled\&quot;&#x60;, &#x60;\&quot;untriggered\&quot;&#x60; or &#x60;\&quot;archive\&quot;&#x60; (if order was archived) */
    public var state: State
    /** User defined label (presented only when previously set for order by user) */
    public var label: String?
    /** Index Price at the moment of trade */
    public var indexPrice: Double
    /** Trade amount. For perpetual and futures - in USD units, for options it is amount of corresponding cryptocurrency contracts, e.g., BTC or ETH. */
    public var amount: Double
    /** Unique instrument identifier */
    public var instrumentName: String
    /** Direction of the \&quot;tick\&quot; (&#x60;0&#x60; &#x3D; Plus Tick, &#x60;1&#x60; &#x3D; Zero-Plus Tick, &#x60;2&#x60; &#x3D; Minus Tick, &#x60;3&#x60; &#x3D; Zero-Minus Tick). */
    public var tickDirection: TickDirection
    /** Always &#x60;null&#x60;, except for a self-trade which is possible only if self-trading is switched on for the account (in that case this will be id of the maker order of the subscriber) */
    public var matchingId: String
    /** Describes what was role of users order: &#x60;\&quot;M\&quot;&#x60; when it was maker order, &#x60;\&quot;T\&quot;&#x60; when it was taker order */
    public var liquidity: Liquidity?

    public init(direction: Direction, feeCurrency: FeeCurrency, orderId: String, timestamp: Int, price: Double, iv: Double?, tradeId: String, fee: Double, orderType: OrderType?, tradeSeq: Int, selfTrade: Bool, state: State, label: String?, indexPrice: Double, amount: Double, instrumentName: String, tickDirection: TickDirection, matchingId: String, liquidity: Liquidity?) {
        self.direction = direction
        self.feeCurrency = feeCurrency
        self.orderId = orderId
        self.timestamp = timestamp
        self.price = price
        self.iv = iv
        self.tradeId = tradeId
        self.fee = fee
        self.orderType = orderType
        self.tradeSeq = tradeSeq
        self.selfTrade = selfTrade
        self.state = state
        self.label = label
        self.indexPrice = indexPrice
        self.amount = amount
        self.instrumentName = instrumentName
        self.tickDirection = tickDirection
        self.matchingId = matchingId
        self.liquidity = liquidity
    }

    public enum CodingKeys: String, CodingKey { 
        case direction
        case feeCurrency = "fee_currency"
        case orderId = "order_id"
        case timestamp
        case price
        case iv
        case tradeId = "trade_id"
        case fee
        case orderType = "order_type"
        case tradeSeq = "trade_seq"
        case selfTrade = "self_trade"
        case state
        case label
        case indexPrice = "index_price"
        case amount
        case instrumentName = "instrument_name"
        case tickDirection = "tick_direction"
        case matchingId = "matching_id"
        case liquidity
    }


}

