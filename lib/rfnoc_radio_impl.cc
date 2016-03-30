/* -*- c++ -*- */
/* Copyright 2015 Ettus Research
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * gr-ettus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gr-ettus; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "rfnoc_radio_impl.h"

namespace gr {
  namespace ettus {

    rfnoc_radio::sptr
    rfnoc_radio::make(
          const device3::sptr &dev,
          const ::uhd::stream_args_t &tx_stream_args,
          const ::uhd::stream_args_t &rx_stream_args,
          const int radio_select,
          const int device_select
    ) {
      return gnuradio::get_initial_sptr(
          new rfnoc_radio_impl(dev, tx_stream_args, rx_stream_args, radio_select, device_select)
      );
    }

    rfnoc_radio_impl::rfnoc_radio_impl(
        const device3::sptr &dev,
        const ::uhd::stream_args_t &tx_stream_args,
        const ::uhd::stream_args_t &rx_stream_args,
        const int radio_select,
        const int device_select
    ) : rfnoc_block("rfnoc_radio"),
        rfnoc_block_impl(
            dev,
            rfnoc_block_impl::make_block_id("Radio", radio_select, device_select),
            tx_stream_args, rx_stream_args
        )
    {
      _radio_ctrl = get_block_ctrl_throw< ::uhd::rfnoc::radio_ctrl >();
    }

    rfnoc_radio_impl::~rfnoc_radio_impl()
    {
      /* nop */
    }

    void rfnoc_radio_impl::set_rate(const double rate)
    {
      _radio_ctrl->set_rate(rate);
    }

    void rfnoc_radio_impl::set_tx_freq(const double freq, const size_t chan)
    {
      _radio_ctrl->set_tx_frequency(freq, chan);
    }

    void rfnoc_radio_impl::set_rx_freq(const double freq, const size_t chan)
    {
      _radio_ctrl->set_rx_frequency(freq, chan);
    }

    void rfnoc_radio_impl::set_tx_gain(const double gain, const size_t chan)
    {
      _radio_ctrl->set_tx_gain(gain, chan);
    }

    void rfnoc_radio_impl::set_rx_gain(const double gain, const size_t chan)
    {
      _radio_ctrl->set_rx_gain(gain, chan);
    }

    void rfnoc_radio_impl::set_tx_antenna(const std::string &ant, const size_t chan)
    {
      _radio_ctrl->set_tx_antenna(ant, chan);
    }

    void rfnoc_radio_impl::set_rx_antenna(const std::string &ant, const size_t chan)
    {
      _radio_ctrl->set_rx_antenna(ant, chan);
    }

    // FIXME everything down from here needs to be mapped on to the block API
    void rfnoc_radio_impl::set_tx_dc_offset(bool enable, const size_t chan)
    {
      get_device()->set_tx_dc_offset(enable, chan);
    }

    void rfnoc_radio_impl::set_tx_dc_offset(const std::complex< double > &offset, const size_t chan)
    {
      get_device()->set_tx_dc_offset(offset, chan);
    }

    void rfnoc_radio_impl::set_rx_dc_offset(bool enable, const size_t chan)
    {
      get_device()->set_rx_dc_offset(enable, chan);
    }

    void rfnoc_radio_impl::set_rx_dc_offset(const std::complex< double > &offset, const size_t chan)
    {
      get_device()->set_rx_dc_offset(offset, chan);
    }

    uhd::time_spec_t rfnoc_radio_impl::get_time_now(void)
    {
      return get_device()->get_time_now();
    }

    void rfnoc_radio_impl::set_command_time(const uhd::time_spec_t &time)
    {
      get_device()->set_command_time(time);
    }

    void rfnoc_radio_impl::clear_command_time(void)
    {
      get_device()->clear_command_time();
    }

  } /* namespace ettus */
} /* namespace gr */

