#include <stdint.h>
#include "vcpu.h"

Vcpu::Vcpu() : n(false), z(false), v(false), c(false)
{
    reg0_ = &memory_[MEM_SIZE + 0];
    reg1_ = &memory_[MEM_SIZE + 1];
    reg2_ = &memory_[MEM_SIZE + 2];
    reg3_ = &memory_[MEM_SIZE + 3];
    reg4_ = &memory_[MEM_SIZE + 4];
    reg5_ = &memory_[MEM_SIZE + 5];
    reg6_ = &memory_[MEM_SIZE + 6];
    reg7_ = &memory_[MEM_SIZE + 7];

    //Shows that video buffer works fine;
    keyboard.stringToVRAM(frameBuffer_, 50, 50, "OSTOROZHNA!");
    keyboard.stringToVRAM(frameBuffer_, 50, 80, "ETO APASNIY");
    keyboard.stringToVRAM(frameBuffer_, 50, 110, "EMULATOR!!!");

}

Vcpu::~Vcpu()
{

}

uint16_t Vcpu::getRegValue(uint16_t numReg)
{
    switch (numReg)
    {
    case 0: { return *reg0_; break; }
    case 1: { return *reg1_; break; }
    case 2: { return *reg2_; break; }
    case 3: { return *reg3_; break; }
    case 4: { return *reg4_; break; }
    case 5: { return *reg5_; break; }
    case 6: { return *reg6_; break; }
    case 7: { return *reg7_; break; }

    default: return 0;
    }
}

uint16_t* Vcpu::getRegAddr(uint16_t numReg)
{
    switch (numReg)
    {
    case 0: { return reg0_; break; }
    case 1: { return reg1_; break; }
    case 2: { return reg2_; break; }
    case 3: { return reg3_; break; }
    case 4: { return reg4_; break; }
    case 5: { return reg5_; break; }
    case 6: { return reg6_; break; }
    case 7: { return reg7_; break; }

    default: return 0;
    }
}

void Vcpu::setRegValue(uint16_t numReg, uint16_t value)
{
    switch (numReg)
    {
    case 0: { *reg0_ = value; break; }
    case 1: { *reg1_ = value; break; }
    case 2: { *reg2_ = value; break; }
    case 3: { *reg3_ = value; break; }
    case 4: { *reg4_ = value; break; }
    case 5: { *reg5_ = value; break; }
    case 6: { *reg6_ = value; break; }
    case 7: { *reg7_ = value; break; }
    }
}

uint16_t Vcpu::getMemValue(uint16_t address)
{
    return memory_[address];
}

uint16_t* Vcpu::getMemAddr(uint16_t address)
{
    return memory_ + address;
}

void Vcpu::setMemValue(uint16_t address, uint16_t value)
{
    memory_[address] = value;
}

bool Vcpu::getMemString(QString& str, uint16_t address)
{
    for (size_t i = 0; i < MEM_SIZE; i++)
    {
        str += "0x" + QString("%1").arg(2*(address+i), 4, 16, QChar('0')) + ": ";
        uint16_t word = this->getMemValue(address+i);
        uint8_t lo = word & 0xFF;
        uint8_t hi = word >> 8;
        str += QString("%1").arg(lo, 2, 16, QChar('0')) + " " + QString("%1").arg(hi, 2, 16, QChar('0'));
        if (i*2 == this->getRegValue(7))
            str += " <<<";
        str += "\n";
    }
    return true;
}

bool Vcpu::getDisasmString(QString& str, uint16_t address)
{
    return getMemString(str, address);
}

bool Vcpu::reset()
{
    for (size_t i = 0; i < REG_AMOUNT; i++)
    {
        *(getRegAddr(i)) = 0;
    }
    n = z = v = c = 0;
    return true;
}

uchar* Vcpu::getFrameBuffer()
{
    return frameBuffer_;
}

bool Vcpu::getFlag(uint16_t flagNum)
{
    switch (flagNum)
    {
        case 0: return n;
        case 1: return z;
        case 2: return v;
        case 3: return c;
        default: return false;
    }

    return false;
}
