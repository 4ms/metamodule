static long _tick = 0;

long HAL_GetTick()
{
	return _tick;
}

void fake_HAL_IncTick()
{
	_tick++;
}
