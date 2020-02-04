/**
 * @file ember-network-parameters.cpp
 *
 * @brief Ember network parameters.
 */

#include <sstream>
#include <iomanip>

#include "ezsp/ezsp-protocol/struct/ember-network-parameters.h"

#include "ezsp/byte-manip.h"

using NSEZSP::CEmberNetworkParameters;

CEmberNetworkParameters::CEmberNetworkParameters() :
	extend_pan_id(0),
	pan_id(0),
	radio_tx_power(3),
	radio_channel(11),
	join_method(EMBER_USE_MAC_ASSOCIATION),
	nwk_manager_id(0),
	nwk_update_id(0),
	channels(0)
{
}

CEmberNetworkParameters::CEmberNetworkParameters(const NSSPI::ByteBuffer& raw_message, const std::string::size_type skip) :
	extend_pan_id(
		static_cast<uint64_t>(raw_message.at(0+skip)) |
		static_cast<uint64_t>(raw_message.at(1+skip))<<8 |
		static_cast<uint64_t>(raw_message.at(2+skip))<<16 |
		static_cast<uint64_t>(raw_message.at(3+skip))<<24 |
		static_cast<uint64_t>(raw_message.at(4+skip))<<32 |
		static_cast<uint64_t>(raw_message.at(5+skip))<<40 |
		static_cast<uint64_t>(raw_message.at(6+skip))<<48 |
		static_cast<uint64_t>(raw_message.at(7+skip))<<56),
	pan_id(dble_u8_to_u16(raw_message.at(9+skip), raw_message.at(8+skip))),
	radio_tx_power(raw_message.at(10+skip)),
	radio_channel(raw_message.at(11+skip)),
	join_method(static_cast<EmberJoinMethod>(raw_message.at(12+skip))),
	nwk_manager_id(static_cast<EmberNodeId>(dble_u8_to_u16(raw_message.at(14+skip), raw_message.at(13+skip)))),
	nwk_update_id(raw_message.at(15+skip)),
	channels(
		static_cast<uint32_t>(raw_message.at(16)) |
		static_cast<uint32_t>(raw_message.at(17))<<8 |
		static_cast<uint32_t>(raw_message.at(18))<<16 |
		static_cast<uint32_t>(raw_message.at(19))<<24)
{
}

NSSPI::ByteBuffer CEmberNetworkParameters::getRaw() const
{
    NSSPI::ByteBuffer raw_message;

    // extend_pan_id
    raw_message.push_back(static_cast<uint8_t>(extend_pan_id&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>8)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>16)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>24)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>32)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>40)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>48)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((extend_pan_id>>56)&0xFF));


    // pan_id
    raw_message.push_back(u16_get_lo_u8(pan_id));
    raw_message.push_back(u16_get_hi_u8(pan_id));

    // radio_tx_power
    raw_message.push_back(static_cast<uint8_t>(radio_tx_power));

    // radio_channel
    raw_message.push_back(static_cast<uint8_t>(radio_channel));

    // join_method
    raw_message.push_back(static_cast<uint8_t>(join_method));

    // nwk_manager_id
    raw_message.push_back(static_cast<uint8_t>(nwk_manager_id&0xFF));
    raw_message.push_back(static_cast<uint8_t>(static_cast<uint8_t>(nwk_manager_id>>8)&0xFF));

    // nwk_update_id
    raw_message.push_back(static_cast<uint8_t>(nwk_update_id));

    // channels
    raw_message.push_back(static_cast<uint8_t>(channels&0xFF));
    raw_message.push_back(static_cast<uint8_t>((channels>>8)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((channels>>16)&0xFF));
    raw_message.push_back(static_cast<uint8_t>((channels>>24)&0xFF));

    return raw_message;
}

std::string CEmberNetworkParameters::String() const
{
    std::stringstream buf;

    buf << "EmberNetworkParameters : { ";
    buf << "[extend_pan_id : "<< std::hex << std::setw(16) << std::setfill('0') << unsigned(extend_pan_id) << "]";
    buf << "[pan_id : "<< std::hex << std::setw(4) << std::setfill('0') << unsigned(pan_id) << "]";
    buf << "[radio_tx_power : "<< std::dec << unsigned(radio_tx_power) << "]";
    buf << "[radio_channel : "<< std::dec << unsigned(radio_channel) << "]";
    buf << "[join_method : "<< CEzspEnum::EmberJoinMethodToString(join_method) << "]";
    buf << "[nwk_manager_id : "<< std::hex << std::setw(4) << std::setfill('0') << unsigned(nwk_manager_id) << "]";
    buf << "[nwk_update_id : "<< std::hex << std::setw(2) << std::setfill('0') << unsigned(nwk_update_id) << "]";
    buf << "[channels : "<< std::hex << std::setw(8) << std::setfill('0') << unsigned(channels) << "]";
    buf << " }";

    return buf.str();
}
