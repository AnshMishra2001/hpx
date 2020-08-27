//  Copyright (c) 2020 Weile Wei
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/libcds/hpx_tls_manager.hpp>
#include <hpx/modules/threading.hpp>
#include <hpx/threading_base/thread_data.hpp>

#include <cds/gc/details/hp_common.h>

#include <atomic>
#include <cstddef>

namespace cds { namespace gc { namespace hp { namespace details {

    CDS_EXPORT_API thread_data* HPXDataHolder::getTLS()
    {
        auto thread_id = hpx::threads::get_self_id();
        std::size_t hpx_tls_data =
            hpx::threads::get_libcds_hazard_pointer_data(thread_id);
        return reinterpret_cast<thread_data*>(hpx_tls_data);
    }

    CDS_EXPORT_API void HPXDataHolder::setTLS(thread_data* new_tls)
    {
        auto thread_id = hpx::threads::get_self_id();
        size_t hp_tls_data = reinterpret_cast<std::size_t>(new_tls);
        hpx::threads::set_libcds_hazard_pointer_data(thread_id, hp_tls_data);
    }

    generic_smr<HPXDataHolder>* hpx_data_holder_instance_ = nullptr;

    CDS_EXPORT_API generic_smr<HPXDataHolder>* HPXDataHolder::getInstance()
    {
        return hpx_data_holder_instance_;
    }

    CDS_EXPORT_API void HPXDataHolder::setInstance(
        generic_smr<HPXDataHolder>* new_instance)
    {
        hpx_data_holder_instance_ = new_instance;
    }
}}}}    // namespace cds::gc::hp::details

namespace hpx { namespace cds {

    std::atomic<std::size_t> hpxthread_manager_wrapper::thread_counter_{0};

}}    // namespace hpx::cds
