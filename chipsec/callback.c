#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conio.h"

#include "config.h"
#include "settings.h"
#include "chipset.h"
#include "spi.h"
#include "fv.h"

static void update_progress_bar(const char *msg, const int progress)
{
	textcolor(RED);
	printf("\r%s %d%%\n", msg, progress);
	textcolor(WHITE);
}

void readspi_callback(UINT32 spibase_addr, UINT32 spi_size, UINT32 spiaddr)
{
	static int prev_step = 0;
	static int next_step = 0;
	static int progress = 0;

	if (spiaddr == spibase_addr)
	{
		prev_step = 0;
		next_step = spibase_addr + (spi_size / 100);
		progress = 0;
		printf("Reading %dkb...\n", spi_size / 1024);
	}

	if (spiaddr > next_step)
	{
		next_step = next_step + (spi_size / 100);
		progress++;

		update_progress_bar("Reading", progress);
	}
}

void writespi_callback(UINT32 spibase_addr, UINT32 spi_size, UINT32 spiaddr)
{
	static int prev_step = 0;
	static int next_step = 0;
	static int progress = 0;

	if (spiaddr == spibase_addr)
	{
		prev_step = 0;
		next_step = spibase_addr + (spi_size / 100);
		progress = 0;

		printf("Writing %dkb...\n", spi_size / 1024);
	}

	if (spiaddr > next_step)
	{
		next_step = next_step + (spi_size / 100);
		progress++;

		update_progress_bar("Writing", progress);
	}
}

void erasespi_callback(UINT32 spibase_addr, UINT32 spi_size, UINT32 spiaddr)
{
	static int prev_step = 0;
	static int next_step = 0;
	static int progress = 0;

	if (spiaddr == spibase_addr)
	{
		prev_step = 0;
		next_step = spibase_addr + (spi_size / 100);
		progress = 0;
		printf("Erasing %dkb...\n", spi_size / 1024);
	}

	if (spiaddr > next_step)
	{
		next_step = next_step + (spi_size / 100);
		progress++;
		update_progress_bar("Erasing", progress);
	}
}

void errorspi_callback(UINT32 spiaddr, UINT16 command)
{
	textcolor(RED);
	printf("Error at SPI address %06x processing %d\n", spiaddr, command);
	textcolor(WHITE);
}
