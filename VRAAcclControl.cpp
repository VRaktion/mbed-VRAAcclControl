#include "VRAAcclControl.h"

VRAAcclControl::VRAAcclControl(
    UUID *p_uuid, EventQueue *p_eq, StateChain *p_stateChain, I2C *p_i2c) : BLEService("acclCtrl", p_uuid, p_eq, p_stateChain),
                                                                                             eq(p_eq),
                                                                                             i2c(p_i2c)
{
    this->acclSens = new LIS2DH(this->i2c, 0);
}

void VRAAcclControl::init()
{
    printf("[acclCtrl] init\r\n");
    this->acclSens->init();
}

void VRAAcclControl::initCharacteristics()
{
    printf("[acclCtrl] init Characteristics\r\n");
    this->addCharacteristic(
        new BLENotifyCharacteristic(
            (uint16_t)VRAAcclControl::Characteristics::Accl,
            4, //size
            this->eq,
            this->defaultInterval,
            this->minInterval,
            this->maxInterval,
            callback(this, &VRAAcclControl::getAccl)));
}

void VRAAcclControl::pastBleInit()
{
    printf("[acclCtrl] pastBleInit\r\n");
    int8_t accl[4]{0};

    this->setGatt(
        (uint16_t)VRAAcclControl::Characteristics::Accl,
        (char*)accl, 4);
}

void VRAAcclControl::onStateOff()
{
    printf("[acclCtrl] off\r\n");
}

void VRAAcclControl::onStateStandby()
{
    printf("[acclCtrl] standby\r\n");
}

void VRAAcclControl::onStateOn()
{
    printf("[acclCtrl] on\r\n");
}

void VRAAcclControl::getAccl()
{
    printf("[acclCtrl] getAccl\r\n");

    int8_t accl[4]{0};
    this->acclSens->getMotion_LR(&accl[0], &accl[1], &accl[2]);

    printf("accl x: %d y: %d z: %d\r\n",
           (int)accl[0], (int)accl[1],
           (int)accl[2]);

    this->setGatt(
        (uint16_t)VRAAcclControl::Characteristics::Accl,
        (char*)accl, 4);//TEST
}