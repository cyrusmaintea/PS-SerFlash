cmd arg Function
0 	0 		Returns driver status
	1 		Returns control line status
	2 		Returns communications mode
	3 		Returns communications speed
	4 		Reads 1 byte
1 	0 System reservation
	1 Sets param value as control line status
	2 Sets param value as communications mode
	3 Sets param value as communications speed
	4 		Writes 1 byte
2 	0 		Resets driver
	1 		Clears driver status error-related bits
	
	
bit		content
31-10 	Undecided
9 		SR_IRQ 1: interrupt on
8 		SR_CTS 1: CTS is on
7 		SR_DSR 1: DSR is on
6 		Undecided
5 		SR_FE 1: frame error occurs
4 		SR_OE 1: overrun error occurs
3 		SR_PERROR 1: parity error occurs
2 		SR_TXU 1: no communications data
1 		SR_RXRDY 1: able to read communications data
0 		SR_TXRDY 1: able to write communications data