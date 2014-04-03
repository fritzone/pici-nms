#pragma once

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>


#define NAME(x) x
#define COND(x) x
#define MUTEX(x) x

#define THREAD(name,x) boost::thread name(&x)
#define THREADWP(name,x,y) boost::thread name(boost::bind(x,y))
#define SCOPEDLOCK(x) boost::mutex::scoped_lock lock(x)
#define DESTROY_SCOPEDLOCK(x) lock.unlock()
#define WAIT(cond,mutex) cond.wait(mutex)
#define NOTIFY_ALL(cond) cond.notify_all()
#define NOTIFY_ONE(cond) cond.notify_one()
#define SLEEP(s) boost::xtime xt; boost::xtime_get(&xt, boost::TIME_UTC);  xt.sec += s; boost::thread::sleep(xt);

