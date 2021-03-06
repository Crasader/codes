#ifndef __AXP192_REGS_H__
#define __AXP192_REGS_H__

//power control register
#define AXP192_POWER_STATE 			0x00
#define AXP192_POWER_MODE			0x01
#define OTG_VBUS_STATE				0x04
#define EXTERN_DCDC2_CONTROL			0x10
#define DCDC1_3_LDO2_3_CONTROL			0x12
#define DCDC1_3_LDO2_3_CONTROL_MASK		0x0F
#define DCDC2_VOLTAGE_SET			0x23
#define DCDC2_VOLTAGE_SET_MASK			0x3F
#define DCDC1_VOLTAGE_SET			0x26
#define DCDC1_VOLTAGE_SET_MASK			0x7F
#define DCDC3_VOLTAGE_SET			0x27
#define DCDC3_VOLTAGE_SET_MASK			0x7F
#define LDO2_3_VOLTAGE_SET			0x28
#define LDO2_VOLTAGE_SET_MASK			0xF0
#define LDO_3_VOLTAGE_SET_MASK			0x0F
#define VBUS_IPS_CONTROL			0x30
#define VHOLD_VOTAGE_MASK			0x38
#define AUTO_POWER_VOLTAGE			0x31
#define AUTO_POWER_VOLTAGE_MASK			0x07
#define POWER_OFF_SETTING			0x32
#define CHANGER_CONTROL_1			0x33
#define CHANGER_CONTROL_2			0x34
#define BACKUP_BAT_CHARGE_CONTROL 		0x35
#define POWERKY_SETTING				0x36
#define DCDC_FREQUENCE_SETTING			0x37
#define CHARGE_LOW_TEMPERATURE			0x38
#define CHARGE_HIGH_TEMPERATURE			0x39
#define APS_VOLTAGET_LOWLEVEL1			0x3A
#define APS_VOLTAGET_LOWLEVEL2			0x3B
#define DISCHARGE_LOW_TEMPERATURE		0x3C
#define DISCHARGE_HIGH_TEMPERATURE		0x3D
#define DCDC_WORK_MODE				0x80
#define DCDC_WORK_MODE_MASK			0x0E
#define ADC_ENABLE_1				0x82
#define ADC_ENABLE_2				0x83
#define ADC_SAMPLE_RATE_SETTING			0x84
#define ADC_INPUT_RANGE				0x85
#define ADC_GPIO1_IRQ_RISING			0x86
#define ADC_GPIO1_IRQ_FALLING			0x87
#define ADC_TIMER_CONTROL			0x8A
#define VBUS_MONITOR_SPR			0x8B
#define HIGH_TEMPERATURE_POWEROFF		0x8F
#define GPIO0_FUNC_SETTING			0x90
#define GPIO0_LDO_VOLTAGE			0x91
#define GPIO0_LDO_VOLTAGE_MASK			0xF0
#define GPIO1_FUNC_SETTING			0x92
#define GPIO2_FUNC_SETTING			0x93
#define GPIO_STATE_MONITOR			0x94
#define GPIO_4_3_FUNC_SETTING			0x95
#define GPIO_4_3_STATE_MONITOR			0x96
#define GPIO_PULLDOWN_SETTING			0x97
#define PWM1_FREQUENCE_SETTING			0x98
#define PWM1_DUTYCYCLE_SETTING_1		0x99
#define PWM1_DUTYCYCLE_SETTING_2		0x9A
#define PWM2_FREQUENCE_SETTING			0x9B
#define PWM2_DUTYCYCLE_SETTING_1		0x9C
#define PWM2_DUTYCYCLE_SETTING_2		0x9D
#define N_RSTO_FUNC_SETTING			0x9E
#define IRQ_ENABLE_1				0x40
#define IRQ_ENABLE_2				0x41
#define IRQ_ENABLE_3				0x42
#define IRQ_ENABLE_4				0x43


#define ACIN_VOLTAGE_HIGH_8			0x56
#define ACIN_VOLTAGE_LOW_4			0x57
#define ACIN_CURRENT_HIGH_8			0x58
#define ACIN_CURRENT_LOW_4			0x59
#define VBUS_VOLTAGE_HIGH_8			0x5A
#define VBUS_VOLTAGE_LOW_4			0x5B
#define VBUS_CURRENT_HIGH_8			0x5C
#define VBUS_CURRENT_LOW_4			0x5D
#define INNER_TEMPERATURE_HIGH_8		0x5E
#define INNER_TEMPERATURE_LOW_4			0x5F
#define BATT_TEMPERATURE_HIGH_8			0x62
#define BATT_TEMPERATURE_LOW_4			0x63
#define GPIO1_VOLTAGE_HIGH_8			0x66
#define GPIO1_VOLTAGE_LOW_4			0x67
#define BATT_INSTANT_POWER_HIGH_8		0x70
#define BATT_INSTANT_POWER_MID_8		0x71
#define BATT_INSTANT_POWER_LOW_8		0x72
#define BATT_VOLTAGE_HIGH_8			0x78
#define BATT_VOLTAGE_LOW_4			0x79
#define BATT_CHARGE_CURRENT_HIGH_8		0x7A
#define BATT_CHARGE_CURRENT_LOW_5		0x7B
#define BATT_DISCHARGE_CURRENT_HIGH_8		0x7C
#define BATT_DISCHARGE_CURRENT_LOW_5		0x7D
#define APS_VOLTAGE_HIGH_8			0x7E
#define APS_VOLTAGE_LOW_4			0x7F
#define CHARGE_COULOMBMETER_3			0xB0
#define CHARGE_COULOMBMETER_2			0xB1
#define CHARGE_COULOMBMETER_1			0xB2
#define CHARGE_COULOMBMETER_0			0xB3
#define DISCHARGE_COULOMBMETER_3		0xB4
#define DISCHARGE_COULOMBMETER_2		0xB5
#define DISCHARGE_COULOMBMETER_1		0xB6
#define DISCHARGE_COULOMBMETER_0		0xB7
#define COULOMBMETER_CONTROL			0xB8


//irq state
#define IRQ_STATE_1				0x44
#define IRQ_STATE_2				0x45
#define IRQ_STATE_3				0x46
#define IRQ_STATE_4				0x47

//ADC 1 enable function
#define ADC_BATT_VOLTAGE_EN			(1<<7)
#define ADC_BATT_CURRENT_EN			(1<<6)
#define ADC_ACIN_VOLTAGE_EN			(1<<5)
#define ADC_ACIN_CURRENT_EN			(1<<4)
#define ADC_VBUS_VOLTAGE_EN			(1<<3)
#define ADC_VBUS_CURRENT_EN			(1<<2)
#define ADC_APS_VOLTAGE_EN			(1<<1)
#define ADC_TS_PIN_EN				(1<<0)

//ADC 2 enable function
#define ADC_AXP192_TEMP_EN			(1<<7)
#define ADC_GPIO0_EN				(1<<3)
#define ADC_GPIO1_EN				(1<<2)
#define ADC_GPIO2_EN				(1<<1)
#define ADC_GPIO3_EN				(1<<0)

//ADC sample rate
#define ADC_SAMPLE_RATE_25			(0<<6)
#define ADC_SAMPLE_RATE_50			(1<<6)
#define ADC_SAMPLE_RATE_100			(2<<6)
#define ADC_SAMPLE_RATE_200			(3<<6)

#define ADC_TS_CURRENT_20			(0<<4)
#define ADC_TS_CURRENT_40			(1<<4)
#define ADC_TS_CURRENT_60			(2<<4)
#define ADC_TS_CURRENT_80			(3<<4)

#define ADC_TS_FUN_TEMP				(0<<2)
#define ADC_TS_FUN_EXT				(1<<2)

#define ADC_TS_CURRENT_MODE_OFF			(0<<0)
#define ADC_TS_CURRENT_MODE_CHARGE		(1<<0)
#define ADC_TS_CURRENT_MODE_SAMPLE		(2<<0)
#define ADC_TS_CURRENT_MODE_ON			(3<<0)

//PEK setting
#define PEK_ON_TIME_128MS			(0<<6)
#define PEK_ON_TIME_256MS			(1<<6)
#define PEK_ON_TIME_512MS			(2<<6)
#define PEK_ON_TIME_1S				(3<<6)
#define PEK_OFF_TIME_4S				(0<<0)
#define PEK_OFF_TIME_6S				(1<<0)
#define PEK_OFF_TIME_8S				(2<<0)
#define PEK_OFF_TIME_10S			(3<<0)
#define PEK_OFF_ENABLE				(1<<3)
#define PEK_LONG_TIME_1S			(0<<4)
#define PEK_LONG_TIME_1_5S			(1<<4)
#define PEK_LONG_TIME_2S			(2<<4)
#define PEK_LONG_TIME_2_5S			(3<<4)

//axp192 too hot power enable
#define HOT_POWER_OFF_ENBALE			(1<<2)

//GPIO0 FUNCTION
#define GPIO0_FUNC_LDO				0x2
#define GPIO0_FUNC_OUTPUT_LOW			0x7
#define GPIO0_CURRENT_3_3			(0xf<<4)

#define CHGLED_CONTROL_MASK			(1<<3)

#define CHARGER_ENABLE_MASK			(1<<7)
#define CHARGER_TARGET_4_2V			(2<<5)
#define CHARGER_TARGET_4_1V			(0<<5)
#define CHARGER_END_CURRENT_MASK		(1<<4)
#define INTER_CHARGE_CURRENT_MASK		(0xf)
#define INTER_CHARGE_CURRENT_100		(0x0)
#define INTER_CHARGE_CURRENT_450		(0x4)
#define INTER_CHARGE_CURRENT_780		(0x8)
#define INTER_CHARGE_CURRENT_MAX		(0xf)

#define VBUS_LIMIT_VHOLD_MASK			(1<<6)
#define VBUS_LIMIT_CURRETN_MASK			(1<<1)
#define VHOLD_4_4V				(4<<3)	

//register IRQ1
#define EVENT_ACIN_OVERVOLTAGE			(1<<7)
#define EVENT_ACIN_PLUGIN			(1<<6)
#define EVENT_ACIN_PLUGOUT			(1<<5)
#define EVENT_VBUS_OVERVOLTAGE			(1<<4)
#define EVENT_VBUS_PLUGIN			(1<<3)
#define EVENT_VBUS_PLUGOUT			(1<<2)
#define EVENT_VBUS_LOW_VHOLD			(1<<1)

//register IRQ2 
#define EVENT_BATT_PLUGIN			(1<<7)<<8
#define EVENT_BATT_PLUGOUT			(1<<6)<<8
#define EVENT_BATT_ACTIVTE			(1<<5)<<8
#define EVENT_BATT_DISACTIVE			(1<<4)<<8
#define EVENT_BATT_CHARGING			(1<<3)<<8
#define EVENT_BATT_CHARGE_END			(1<<2)<<8
#define EVENT_BATT_HOT				(1<<1)<<8
#define EVENT_BATT_COLD				(1<<0)<<8

//register IRQ3 
#define EVENT_CHIP_HOT				(1<<7)<<16
#define EVENT_CHARGE_CURRENT_LOW		(1<<6)<<16
#define EVENT_DCDC1_OUPUT_LOW			(1<<5)<<16
#define EVENT_DCDC2_OUPUT_LOW			(1<<4)<<16
#define EVENT_DCDC3_OUPUT_LOW			(1<<3)<<16
#define EVENT_SHORT_KEY				(1<<1)<<16
#define EVENT_LONG_KEY				(1<<0)<<16

//register IRQ4
#define EVENT_N_OE_POWERON			(1<<7)<<24
#define EVENT_N_OE_POWEROFF			(1<<6)<<24
#define EVENT_VBUS_VALID			(1<<5)<<24
#define EVENT_VBUS_INVALID			(1<<4)<<24
#define EVENT_VBUS_SESSION_AB			(1<<3)<<24
#define EVENT_VBUS_SESSION_END			(1<<2)<<24
#define EVENT_LOW_POWER_WARNING			(1<<0)<<24

//register IRQ5
#define EVENT_TIMEOUT				((1ULL<<7))<<32
#define EVENT_GPIO2				((1ULL<<2))<<32
#define EVENT_GPIO1				((1ULL<<1))<<32
#define EVENT_GPIO0				((1ULL<<0))<<32

//led status
#define AXP192_LED_OFF				(0<<4)
#define AXP192_LED_1HZ				(1<<4)
#define AXP192_LED_4HZ				(2<<4)
#define AXP192_LED_ON				(3<<4)

//led frequence
#define HZ_1					(0x1)
#define HZ_4					(0x4)

#endif
