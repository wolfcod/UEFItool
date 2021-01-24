#ifndef __CALLBACK_H
#define __CALLBACK_H

void readspi_callback(UINT32 spibase_addr, UINT32 spi_size, UINT32 spiaddr);
void writespi_callback(UINT32 spibase_addr, UINT32 spi_size, UINT32 spiaddr);
void erasespi_callback(UINT32 spibase_addr, UINT32 spi_size, UINT32 spiaddr);
void errorspi_callback(UINT32 spiaddr, UINT16 command);

#endif
