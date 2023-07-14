#include "main.h"
#include "timer.h"

unsigned long CTimer::m_wCountTimer = 0;
unsigned long CTimer::m_wCountTick_RealmSec = 0;

CTimer::CTimer(unsigned long lDefaultTime, bool bONEvent, bool bON) {
	SetDefault(lDefaultTime, bONEvent);
	Tm.On = bON;
	m_wCountTimer++;
}

CTimer::~CTimer() {
	m_wCountTimer--;
}

unsigned long CTimer::GetCurrentTime(void) {             // for up to one minute
	unsigned mS;

	if (Tm.On) {
		mS = m_wCountTick_RealmSec - m_wCountTick_start;
		if (m_wCountTick <= mS) {
			Tm.Fl = TIMEREVENT_ON;
			Tm.On = TIMER_OFF;
			mS = (unsigned) m_wCountTick;
		}
	} else
		mS = (unsigned) m_wCountTick;

	return mS;
}

void CTimer::Run(void) {
	if (Tm.On) {
		if (m_wCountTick <= (m_wCountTick_RealmSec - m_wCountTick_start)) {
			Tm.Fl = TIMEREVENT_ON;
			Tm.On = TIMER_OFF;
		}
	}
}

unsigned long CTimer::GetDefault(void) {
	return ((unsigned long) m_wCountTick);
}

void CTimer::SetDefault(unsigned long lDefaultTime, bool bONEvent) {
	Tm.mSec = 1;

	m_wCountTick = m_wDefaultCountTick = lDefaultTime;
	m_wCountTick_start = m_wCountTick_RealmSec;

	Tm.On = TIMER_ON;
	Tm.Fl = bONEvent;
}

void CTimer::Set(unsigned long lTime) {
	m_wCountTick = lTime;
	m_wCountTick_start = m_wCountTick_RealmSec;

	Tm.On = TIMER_ON;
	Tm.Fl = TIMEREVENT_OFF;
}

void CTimer::Reset(void) {
	m_wCountTick = m_wDefaultCountTick;
	m_wCountTick_start = m_wCountTick_RealmSec;

	Tm.On = TIMER_ON;
	Tm.Fl = TIMEREVENT_OFF;
}

void CTimer::Off(void) {
	Tm.On = TIMER_OFF;
	Tm.Fl = TIMEREVENT_OFF;
}

void CTimer::SetEvent(void) {
	Tm.On = TIMER_OFF;
	Tm.Fl = TIMEREVENT_ON;
}

bool CTimer::GetEvent(void) {
	Run();
	return (bool) Tm.Fl;
}
bool CTimer::IsEvent(void) {
	return (bool) Tm.Fl;
}
bool CTimer::IsOn(void) {
	return (bool) (Tm.On || Tm.Fl);
}
bool CTimer::IsOff(void) {
	return (bool) (!(Tm.On || Tm.Fl));
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM6) {
		CTimer::m_wCountTick_RealmSec++;
	}
}

