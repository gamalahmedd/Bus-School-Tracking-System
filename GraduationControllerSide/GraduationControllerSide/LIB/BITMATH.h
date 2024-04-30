#ifndef BITMATH_H_
#define BITMATH_H_

#define SetBit(Reg,BitNo) (Reg |=(1<<BitNo))
#define ClearBit(Reg,BitNo) (Reg &=~(1<<BitNo))
#define ToggleBit(Reg,BitNo) (Reg ^=(1<<BitNo))
#define ReadBit(Reg,BitNo) ((Reg & (1 << BitNo)) >> BitNo)

#endif /* BITMATH_H_ */