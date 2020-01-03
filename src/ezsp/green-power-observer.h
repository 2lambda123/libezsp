/**
 * @file green-power-observer.h
 *
 * @brief Describes the interface for an observer that wants to process incoming green power frames
 */
#pragma once

#include <stdbool.h>

#include <ezsp/gpd.h>

#include "ezsp/zbmessage/green-power-frame.h"

namespace NSEZSP {

class CGpObserver {
public:
    CGpObserver() {};
    virtual ~CGpObserver() = default;

    /**
     * @brief Method that will be invoked on incoming valid green power frames
     *
     * @param i_gpf The green power frame received
     */
    virtual void handleRxGpFrame( CGpFrame &i_gpf ) = 0;

    /**
     * @brief Method that will be invoked on every green power frame receive on our radio channel
     *
     * @param i_gpd_source_id The green power device id observe
     * @param i_gpd_known The green power device is known by the sink
     * @param i_gpd_key_status Status of key for this GPD
     */
    virtual void handleRxGpdId( uint32_t &i_gpd_id, bool i_gpd_known, CGpdKeyStatus i_gpd_key_status ) = 0;

};

} // namespace NSEZSP
