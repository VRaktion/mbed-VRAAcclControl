#ifndef VRA_ACCL_CONTROL_H
#define VRA_ACCL_CONTROL_H

#include "BLEService.h"

#include "BLENotifyCharacteristic.h"

#include "LIS2DH.h"

class VRAAcclControl : public BLEService
{
public:
    enum class Characteristics : uint16_t
    {
        Accl = 0xFF00,
    };

    VRAAcclControl(UUID *p_uuid, EventQueue *p_eq, StateChain *p_stateChain, I2C *p_i2c);

    void init();

    void initCharacteristics();
    void pastBleInit();

private:

    void getAccl();

    void onStateOff();
    void onStateStandby();
    void onStateOn();

    EventQueue *eq;
    // VRASettings *settings;
    // VRAStorage *storage;

    I2C *i2c;

    LIS2DH *acclSens;

    static constexpr int defaultInterval{1000};
    static constexpr int minInterval{100};
    static constexpr int maxInterval{600000};
};

#endif //VRA_ACCL_CONTROL_H