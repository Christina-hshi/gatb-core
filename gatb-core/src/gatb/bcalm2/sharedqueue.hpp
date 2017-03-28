#pragma once
// from http://stackoverflow.com/questions/36762248/why-is-stdqueue-not-thread-safe

#include <queue>
#include <mutex>
#include <condition_variable>

    template <typename T>
    class SharedQueue
    {
    public:
        SharedQueue(){};
        ~SharedQueue(){};
        SharedQueue(const SharedQueue&) = delete;

        T& front()
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            while (queue_.empty())
            {
                cond_.wait(mlock);
            }
            return queue_.front();
        }


        void pop_front()
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            while (queue_.empty())
            {
                cond_.wait(mlock);
            }
            queue_.pop_front();
        }     


        bool pop_immediately(T& item)
        {
            if (queue_.empty())
                return false;
            item = queue_.front();
            queue_.pop_front();
            return true;
        }

        void push_back(const T& item)
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            queue_.push_back(item);
            mlock.unlock();     // unlock before notificiation to minimize mutex con
            cond_.notify_one(); // notify one waiting thread

        }
        void push_back(T&& item)
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            queue_.push_back(std::move(item));
            mlock.unlock();     // unlock before notificiation to minimize mutex con
            cond_.notify_one(); // notify one waiting thread

        }


        int size()
        {
            std::unique_lock<std::mutex> mlock(mutex_);
            int size = queue_.size();
            mlock.unlock();
            return size;
        }    
        
        bool empty()
        {
            return queue_.empty();
        }


    private:
        std::deque<T> queue_;
        mutable std::mutex mutex_;
        std::condition_variable cond_;
    }; 


         

    

    
