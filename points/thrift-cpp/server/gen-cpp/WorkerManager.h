/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef WorkerManager_H
#define WorkerManager_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "worker_types.h"

namespace freebird
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250) //inheriting methods via dominance
#endif

class WorkerManagerIf {
public:
    virtual ~WorkerManagerIf()
    {
    }
    virtual void ping() = 0;
    virtual int32_t max(const int32_t a, const int32_t b) = 0;
    virtual int32_t gcd(const int32_t p, const int32_t q) = 0;
};

class WorkerManagerIfFactory {
public:
    typedef WorkerManagerIf Handler;

    virtual ~WorkerManagerIfFactory()
    {
    }

    virtual WorkerManagerIf *
    getHandler(const ::apache::thrift::TConnectionInfo &connInfo) = 0;
    virtual void releaseHandler(WorkerManagerIf * /* handler */) = 0;
};

class WorkerManagerIfSingletonFactory : virtual public WorkerManagerIfFactory {
public:
    WorkerManagerIfSingletonFactory(
        const ::std::shared_ptr<WorkerManagerIf> &iface)
        : iface_(iface)
    {
    }
    virtual ~WorkerManagerIfSingletonFactory()
    {
    }

    virtual WorkerManagerIf *
    getHandler(const ::apache::thrift::TConnectionInfo &)
    {
        return iface_.get();
    }
    virtual void releaseHandler(WorkerManagerIf * /* handler */)
    {
    }

protected:
    ::std::shared_ptr<WorkerManagerIf> iface_;
};

class WorkerManagerNull : virtual public WorkerManagerIf {
public:
    virtual ~WorkerManagerNull()
    {
    }
    void ping()
    {
        return;
    }
    int32_t max(const int32_t /* a */, const int32_t /* b */)
    {
        int32_t _return = 0;
        return _return;
    }
    int32_t gcd(const int32_t /* p */, const int32_t /* q */)
    {
        int32_t _return = 0;
        return _return;
    }
};

class WorkerManager_ping_args {
public:
    WorkerManager_ping_args(const WorkerManager_ping_args &);
    WorkerManager_ping_args &operator=(const WorkerManager_ping_args &);
    WorkerManager_ping_args()
    {
    }

    virtual ~WorkerManager_ping_args() noexcept;

    bool operator==(const WorkerManager_ping_args & /* rhs */) const
    {
        return true;
    }
    bool operator!=(const WorkerManager_ping_args &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const WorkerManager_ping_args &) const;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

class WorkerManager_ping_pargs {
public:
    virtual ~WorkerManager_ping_pargs() noexcept;

    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

class WorkerManager_ping_result {
public:
    WorkerManager_ping_result(const WorkerManager_ping_result &);
    WorkerManager_ping_result &operator=(const WorkerManager_ping_result &);
    WorkerManager_ping_result()
    {
    }

    virtual ~WorkerManager_ping_result() noexcept;

    bool operator==(const WorkerManager_ping_result & /* rhs */) const
    {
        return true;
    }
    bool operator!=(const WorkerManager_ping_result &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const WorkerManager_ping_result &) const;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

class WorkerManager_ping_presult {
public:
    virtual ~WorkerManager_ping_presult() noexcept;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
};

typedef struct _WorkerManager_max_args__isset {
    _WorkerManager_max_args__isset() : a(false), b(false)
    {
    }
    bool a : 1;
    bool b : 1;
} _WorkerManager_max_args__isset;

class WorkerManager_max_args {
public:
    WorkerManager_max_args(const WorkerManager_max_args &);
    WorkerManager_max_args &operator=(const WorkerManager_max_args &);
    WorkerManager_max_args() : a(0), b(0)
    {
    }

    virtual ~WorkerManager_max_args() noexcept;
    int32_t a;
    int32_t b;

    _WorkerManager_max_args__isset __isset;

    void __set_a(const int32_t val);

    void __set_b(const int32_t val);

    bool operator==(const WorkerManager_max_args &rhs) const
    {
        if (!(a == rhs.a))
            return false;
        if (!(b == rhs.b))
            return false;
        return true;
    }
    bool operator!=(const WorkerManager_max_args &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const WorkerManager_max_args &) const;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

class WorkerManager_max_pargs {
public:
    virtual ~WorkerManager_max_pargs() noexcept;
    const int32_t *a;
    const int32_t *b;

    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

typedef struct _WorkerManager_max_result__isset {
    _WorkerManager_max_result__isset() : success(false)
    {
    }
    bool success : 1;
} _WorkerManager_max_result__isset;

class WorkerManager_max_result {
public:
    WorkerManager_max_result(const WorkerManager_max_result &);
    WorkerManager_max_result &operator=(const WorkerManager_max_result &);
    WorkerManager_max_result() : success(0)
    {
    }

    virtual ~WorkerManager_max_result() noexcept;
    int32_t success;

    _WorkerManager_max_result__isset __isset;

    void __set_success(const int32_t val);

    bool operator==(const WorkerManager_max_result &rhs) const
    {
        if (!(success == rhs.success))
            return false;
        return true;
    }
    bool operator!=(const WorkerManager_max_result &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const WorkerManager_max_result &) const;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

typedef struct _WorkerManager_max_presult__isset {
    _WorkerManager_max_presult__isset() : success(false)
    {
    }
    bool success : 1;
} _WorkerManager_max_presult__isset;

class WorkerManager_max_presult {
public:
    virtual ~WorkerManager_max_presult() noexcept;
    int32_t *success;

    _WorkerManager_max_presult__isset __isset;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
};

typedef struct _WorkerManager_gcd_args__isset {
    _WorkerManager_gcd_args__isset() : p(false), q(false)
    {
    }
    bool p : 1;
    bool q : 1;
} _WorkerManager_gcd_args__isset;

class WorkerManager_gcd_args {
public:
    WorkerManager_gcd_args(const WorkerManager_gcd_args &);
    WorkerManager_gcd_args &operator=(const WorkerManager_gcd_args &);
    WorkerManager_gcd_args() : p(0), q(0)
    {
    }

    virtual ~WorkerManager_gcd_args() noexcept;
    int32_t p;
    int32_t q;

    _WorkerManager_gcd_args__isset __isset;

    void __set_p(const int32_t val);

    void __set_q(const int32_t val);

    bool operator==(const WorkerManager_gcd_args &rhs) const
    {
        if (!(p == rhs.p))
            return false;
        if (!(q == rhs.q))
            return false;
        return true;
    }
    bool operator!=(const WorkerManager_gcd_args &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const WorkerManager_gcd_args &) const;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

class WorkerManager_gcd_pargs {
public:
    virtual ~WorkerManager_gcd_pargs() noexcept;
    const int32_t *p;
    const int32_t *q;

    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

typedef struct _WorkerManager_gcd_result__isset {
    _WorkerManager_gcd_result__isset() : success(false)
    {
    }
    bool success : 1;
} _WorkerManager_gcd_result__isset;

class WorkerManager_gcd_result {
public:
    WorkerManager_gcd_result(const WorkerManager_gcd_result &);
    WorkerManager_gcd_result &operator=(const WorkerManager_gcd_result &);
    WorkerManager_gcd_result() : success(0)
    {
    }

    virtual ~WorkerManager_gcd_result() noexcept;
    int32_t success;

    _WorkerManager_gcd_result__isset __isset;

    void __set_success(const int32_t val);

    bool operator==(const WorkerManager_gcd_result &rhs) const
    {
        if (!(success == rhs.success))
            return false;
        return true;
    }
    bool operator!=(const WorkerManager_gcd_result &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const WorkerManager_gcd_result &) const;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
    uint32_t write(::apache::thrift::protocol::TProtocol *oprot) const;
};

typedef struct _WorkerManager_gcd_presult__isset {
    _WorkerManager_gcd_presult__isset() : success(false)
    {
    }
    bool success : 1;
} _WorkerManager_gcd_presult__isset;

class WorkerManager_gcd_presult {
public:
    virtual ~WorkerManager_gcd_presult() noexcept;
    int32_t *success;

    _WorkerManager_gcd_presult__isset __isset;

    uint32_t read(::apache::thrift::protocol::TProtocol *iprot);
};

class WorkerManagerClient : virtual public WorkerManagerIf {
public:
    WorkerManagerClient(
        std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot)
    {
        setProtocol(prot);
    }
    WorkerManagerClient(
        std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot,
        std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot)
    {
        setProtocol(iprot, oprot);
    }

private:
    void
    setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot)
    {
        setProtocol(prot, prot);
    }
    void
    setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot,
                std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot)
    {
        piprot_ = iprot;
        poprot_ = oprot;
        iprot_ = iprot.get();
        oprot_ = oprot.get();
    }

public:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol()
    {
        return piprot_;
    }
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol()
    {
        return poprot_;
    }
    void ping();
    void send_ping();
    void recv_ping();
    int32_t max(const int32_t a, const int32_t b);
    void send_max(const int32_t a, const int32_t b);
    int32_t recv_max();
    int32_t gcd(const int32_t p, const int32_t q);
    void send_gcd(const int32_t p, const int32_t q);
    int32_t recv_gcd();

protected:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
    ::apache::thrift::protocol::TProtocol *iprot_;
    ::apache::thrift::protocol::TProtocol *oprot_;
};

class WorkerManagerProcessor : public ::apache::thrift::TDispatchProcessor {
protected:
    ::std::shared_ptr<WorkerManagerIf> iface_;
    virtual bool dispatchCall(::apache::thrift::protocol::TProtocol *iprot,
                              ::apache::thrift::protocol::TProtocol *oprot,
                              const std::string &fname, int32_t seqid,
                              void *callContext);

private:
    typedef void (WorkerManagerProcessor::*ProcessFunction)(
        int32_t, ::apache::thrift::protocol::TProtocol *,
        ::apache::thrift::protocol::TProtocol *, void *);
    typedef std::map<std::string, ProcessFunction> ProcessMap;
    ProcessMap processMap_;
    void process_ping(int32_t seqid,
                      ::apache::thrift::protocol::TProtocol *iprot,
                      ::apache::thrift::protocol::TProtocol *oprot,
                      void *callContext);
    void process_max(int32_t seqid,
                     ::apache::thrift::protocol::TProtocol *iprot,
                     ::apache::thrift::protocol::TProtocol *oprot,
                     void *callContext);
    void process_gcd(int32_t seqid,
                     ::apache::thrift::protocol::TProtocol *iprot,
                     ::apache::thrift::protocol::TProtocol *oprot,
                     void *callContext);

public:
    WorkerManagerProcessor(::std::shared_ptr<WorkerManagerIf> iface)
        : iface_(iface)
    {
        processMap_["ping"] = &WorkerManagerProcessor::process_ping;
        processMap_["max"] = &WorkerManagerProcessor::process_max;
        processMap_["gcd"] = &WorkerManagerProcessor::process_gcd;
    }

    virtual ~WorkerManagerProcessor()
    {
    }
};

class WorkerManagerProcessorFactory
    : public ::apache::thrift::TProcessorFactory {
public:
    WorkerManagerProcessorFactory(
        const ::std::shared_ptr<WorkerManagerIfFactory> &handlerFactory)
        : handlerFactory_(handlerFactory)
    {
    }

    ::std::shared_ptr< ::apache::thrift::TProcessor>
    getProcessor(const ::apache::thrift::TConnectionInfo &connInfo);

protected:
    ::std::shared_ptr<WorkerManagerIfFactory> handlerFactory_;
};

class WorkerManagerMultiface : virtual public WorkerManagerIf {
public:
    WorkerManagerMultiface(
        std::vector<std::shared_ptr<WorkerManagerIf> > &ifaces)
        : ifaces_(ifaces)
    {
    }
    virtual ~WorkerManagerMultiface()
    {
    }

protected:
    std::vector<std::shared_ptr<WorkerManagerIf> > ifaces_;
    WorkerManagerMultiface()
    {
    }
    void add(::std::shared_ptr<WorkerManagerIf> iface)
    {
        ifaces_.push_back(iface);
    }

public:
    void ping()
    {
        size_t sz = ifaces_.size();
        size_t i = 0;
        for (; i < (sz - 1); ++i) {
            ifaces_[i]->ping();
        }
        ifaces_[i]->ping();
    }

    int32_t max(const int32_t a, const int32_t b)
    {
        size_t sz = ifaces_.size();
        size_t i = 0;
        for (; i < (sz - 1); ++i) {
            ifaces_[i]->max(a, b);
        }
        return ifaces_[i]->max(a, b);
    }

    int32_t gcd(const int32_t p, const int32_t q)
    {
        size_t sz = ifaces_.size();
        size_t i = 0;
        for (; i < (sz - 1); ++i) {
            ifaces_[i]->gcd(p, q);
        }
        return ifaces_[i]->gcd(p, q);
    }
};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class WorkerManagerConcurrentClient : virtual public WorkerManagerIf {
public:
    WorkerManagerConcurrentClient(
        std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot,
        std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo>
            sync)
        : sync_(sync)
    {
        setProtocol(prot);
    }
    WorkerManagerConcurrentClient(
        std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot,
        std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot,
        std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo>
            sync)
        : sync_(sync)
    {
        setProtocol(iprot, oprot);
    }

private:
    void
    setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot)
    {
        setProtocol(prot, prot);
    }
    void
    setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot,
                std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot)
    {
        piprot_ = iprot;
        poprot_ = oprot;
        iprot_ = iprot.get();
        oprot_ = oprot.get();
    }

public:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol()
    {
        return piprot_;
    }
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol()
    {
        return poprot_;
    }
    void ping();
    int32_t send_ping();
    void recv_ping(const int32_t seqid);
    int32_t max(const int32_t a, const int32_t b);
    int32_t send_max(const int32_t a, const int32_t b);
    int32_t recv_max(const int32_t seqid);
    int32_t gcd(const int32_t p, const int32_t q);
    int32_t send_gcd(const int32_t p, const int32_t q);
    int32_t recv_gcd(const int32_t seqid);

protected:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
    std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
    ::apache::thrift::protocol::TProtocol *iprot_;
    ::apache::thrift::protocol::TProtocol *oprot_;
    std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

} // namespace freebird

#endif
