#ifndef GOFOR_CPP
#define GOFOR_CPP

#include "used.hpp"
#include <chrono>
#include <cmath>

// rename clock
using Clock = std::chrono::steady_clock;

// return sys-time point
inline int timepoint()
{
    return static_cast< int >( std::chrono::duration_cast< std::chrono::milliseconds >( Clock::now().time_since_epoch() ).count() );
}

inline int timepast( int begintime )
{
    return timepoint() - begintime;
}

// speed up 
void thgofor_a( float sta, float sto, int duration, std::atomic< float >& val )
{
    const int   start = timepoint();
    const float a     = 2.0f * ( sto - sta ) / ( duration * duration );

    while ( true )
        {
            const int   elapsed = timepast( start );
            const float t       = static_cast< float >( elapsed );

            if ( t >= duration )
                {
                    val.store( sto );
                    break;
                }

            const float current = sta + a * t * t / 2.0f;
            val.store( current );
            ege::api_sleep( 1 );
        }
}

// speed down
void thgofor_b( float sta, float sto, int duration, std::atomic< float >& val )
{
    const int   start     = timepoint();
    const float a         = -2.0f * ( sto - sta ) / ( duration * duration );
    const float sqrt_term = std::sqrt( ( -a ) * ( sto - sta ) );

    while ( true )
        {
            const int   elapsed = timepast( start );
            const float t       = static_cast< float >( elapsed );

            if ( t >= duration )
                {
                    val.store( sto );
                    break;
                }

            const float current = sta + sqrt_term - a * t * t / 2.0f;
            val.store( current );
            ege::api_sleep( 1 );
        }
}

// linear move
void thgfor_l( float sta, float sto, int duration, std::atomic< float >& val )
{
    const int   start = timepoint();
    const float speed = ( sto - sta ) / duration;

    while ( true )
        {
            const int   elapsed = timepast( start );
            const float t       = static_cast< float >( elapsed );

            if ( t >= duration )
            {
                    val.store( sto );
                    break;
                }

            const float current = sta + speed * t;
            val.store( current );
            ege::api_sleep( 1 );
        }
}

// Smooth Ease-In-Out
void thgfor_s( float sta, float sto, int duration, std::atomic< float >& val )
{
    const int start = timepoint();

    while ( true )
        {
            const int   elapsed = timepast( start );
            const float t       = static_cast< float >( elapsed ) / duration;

            if ( t >= 1.0f )
                {
                    val.store( sto );
                    break;
                }

            const float smooth_t = t * t * ( 3.0f - 2.0f * t );  // 三阶贝塞尔曲线
            const float current  = sta + ( sto - sta ) * smooth_t;
            val.store( current );
            ege::api_sleep( 1 );
        }
}
#endif
