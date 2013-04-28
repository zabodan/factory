#pragma once
#include "SpinLock.h"
#include <boost/noncopyable.hpp>
#include <memory>

namespace core
{
    template <class T>
    class SingletonBase : private boost::noncopyable
    {
    public:

        static T& instance()
        {
            T* tmp = privateInstance().load(boost::memory_order_consume);
            if (!tmp)
            {
                SpinLock::Guard guard(initLock());

                tmp = privateInstance().load(boost::memory_order_consume);
                if (!tmp)
                {
                    tmp = new T;
                    privateInstance().store(tmp, boost::memory_order_release);
                    sharedInstance().reset(tmp);
                }
            }

            return *tmp;
        }

    private:

        template <class R>
        friend class DependsOn;

        static SpinLock& initLock()
        {
            static SpinLock s_initLock;
            return s_initLock;
        }

        static boost::atomic<T*>& privateInstance()
        {
            static boost::atomic<T*> s_instance;
            return s_instance;
        }

        static std::shared_ptr<T>& sharedInstance()
        {
            static std::shared_ptr<T> s_instance;
            return s_instance;
        }
    };

    template <class R>
    class DependsOn
    {
    public:

        DependsOn()
        {
            R::instance();
            m_required = R::sharedInstance();
        }

    private:

        std::shared_ptr<R> m_required;
    };
}
