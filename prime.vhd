library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity prime is
	port
	(
		b0	:	in std_logic;
		b1	:	in std_logic;
		b2	:	in std_logic;
		b3	:	in std_logic;
		en	:	in std_logic;
		
		d0	:	out std_logic;
		d1	:	out std_logic
	);
end entity;

architecture rtl of prime is
begin
	process(en)
	begin
		if (en = '1') then
			d0 <= '0';
			d1 <= '0';
			
			--Primes
			d0 <= 
			(
				((not b3) and b0) or									--1 , 3 , 5 , 7
				((not b3) and (not b2) and b1) or				--2 , 3
				((not b2) and b1 and b0) or						--3, 11
				(b2 and (not b1) and b0)							--5, 13
			);
			
			--Squares
			d1 <=
			(
				((not b2) and (not b1) and b0) or				--1 = 1^2 , 9 = 3^2
				((not b3) and b2 and (not b1) and (not b0))	--4 = 2^2
			);
		else
			d0 <= '0';
			d1 <= '0';
		end if;
	end process;
end rtl;