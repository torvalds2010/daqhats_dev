#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <daqhats/daqhats.h>

uint8_t address;
uint8_t channel;
int done;

void isr(void* data)
{
    uint8_t value;
    uint8_t test;
    
    // interrupt occurred, make sure we were the source
    mcc152_dio_int_status_read_bit(address, channel, &value);
    if (value == 1)
    {
        done = 1;
        // clear the interrupt
        mcc152_dio_input_read_bit(address, channel, &value);

        test = *(uint8_t*)data;
        printf("Input changed to %d, data = %d\n", value, test);
    }
}

int main(int argc, char* argv[])
{
    uint8_t value;

    // Use MCC 152 at address 0
    address = 0;
    channel = 0;
    done = 0;

    if (mcc152_open(address) != RESULT_SUCCESS)
    {
        printf("No MCC 152 at address 0\n");
        return 1;
    }

    // reset to default DIO settings
    mcc152_dio_reset(address);
    
    // read initial value
    mcc152_dio_input_read_bit(address, channel, &value);
    printf("Current channel %d value is %d\n", channel, value);
    printf("Waiting for change\n");
    
    // enable interrupt only on this channel, mask all others
    mcc152_dio_config_write_bit(address, channel, DIO_INT_MASK, 0);
    
#if 1
    value = 5;
    hat_interrupt_callback_enable(isr, &value);
    
    while (done == 0)
    {
        usleep(1000);
    }
    
    hat_interrupt_callback_disable();
#else    
    // Wait for the input to change. The interrupt can also be generated by
    // another MCC 152 if it is configured for interrupts; monitoring multiple
    // boards is beyond the scope of this example.
    done = 0;
    do
    {
        // wait forever for interrupt
        hat_wait_for_interrupt(-1);
        // interrupt occurred, make sure we were the source
        mcc152_dio_int_status_read_bit(address, channel, &value);
        if (value == 1)
        {
            done = 1;
        }
        // clear the interrupt
        mcc152_dio_input_read_bit(address, channel, &value);
    } while (!done);
    
    printf("Input changed to %d\n", value);
#endif
    
    mcc152_close(address);
    return 0;
}
