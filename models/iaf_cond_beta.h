/*
 *  iaf_cond_beta.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef IAF_COND_BETA_H
#define IAF_COND_BETA_H

// Generated includes:
#include "config.h"

#ifdef HAVE_GSL

// C includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

// Includes from nestkernel:
#include "archiving_node.h"
#include "connection.h"
#include "event.h"
#include "nest_types.h"
#include "recordables_map.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

namespace nest
{
/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 */
extern "C" int iaf_cond_beta_dynamics( double, const double*, double*, void* );

/* BeginUserDocs: neuron, integrate-and-fire, conductance-based, hard threshold

Short description
+++++++++++++++++

Simple conductance based leaky integrate-and-fire neuron model

Description
+++++++++++

``iaf_cond_beta`` is an implementation of a spiking neuron using IAF dynamics with
conductance-based synapses. Incoming spike events induce a postsynaptic change
of conductance modelled by a beta function. The beta function
is normalized such that an event of weight 1.0 results in a peak conductance of
1 nS at :math:`t = \tau_{rise\_[ex|in]}`.

.. note::
   Per 2009-04-17, this class has been revised to our newest
   insights into class design. Please use THIS CLASS as a reference
   when designing your own models with nonlinear dynamics.
   One weakness of this class is that it distinguishes between
   inputs to the two synapses by the sign of the synaptic weight.
   It would be better to use ``receptor_types``, cf ``iaf_cond_alpha_mc``.

See also [1]_, [2]_, [3]_, [4]_, [5]_.

Parameters
++++++++++

The following parameters can be set in the status dictionary.

============= ====== =========================================================
 V_m          mV      Membrane potential
 E_L          mV      Leak reversal potential
 C_m          pF      Capacity of the membrane
 t_ref        ms      Duration of refractory period
 V_th         mV      Spike threshold
 V_reset      mV      Reset potential of the membrane
 E_ex         mV      Excitatory reversal potential
 E_in         mV      Inhibitory reversal potential
 g_L          nS      Leak conductance
 tau_rise_ex  ms      Rise time of the excitatory synaptic beta function
 tau_decay_ex ms      Decay time of the excitatory synaptic beta function
 tau_rise_in  ms      Rise time of the inhibitory synaptic beta function
 tau_decay_in ms      Decay time of the inhibitory synaptic beta function
 I_e          pA      Constant input current
============= ====== =========================================================


Sends
+++++

SpikeEvent

Receives
++++++++

SpikeEvent, CurrentEvent, DataLoggingRequest

References
++++++++++

.. [1] Meffin H, Burkitt AN, Grayden DB (2004). An analytical
       model for the large, fluctuating synaptic conductance state typical of
       neocortical neurons in vivo. Journal of Computational Neuroscience,
       16:159-175.
       DOI: https://doi.org/10.1023/B:JCNS.0000014108.03012.81
.. [2] Bernander O, Douglas RJ, Martin KAC, Koch C (1991). Synaptic background
       activity influences spatiotemporal integration in single pyramidal
       cells.  Proceedings of the National Academy of Science USA,
       88(24):11569-11573.
       DOI: https://doi.org/10.1073/pnas.88.24.11569
.. [3] Kuhn A, Rotter S (2004) Neuronal integration of synaptic input in
       the fluctuation- driven regime. Journal of Neuroscience,
       24(10):2345-2356
       DOI: https://doi.org/10.1523/JNEUROSCI.3349-03.2004
.. [4] Rotter S,  Diesmann M (1999). Exact simulation of time-invariant linear
       systems with applications to neuronal modeling. Biologial Cybernetics
       81:381-402.
       DOI: https://doi.org/10.1007/s004220050570
.. [5] Roth A and van Rossum M (2010). Chapter 6: Modeling synapses.
       in De Schutter, Computational Modeling Methods for Neuroscientists,
       MIT Press.


See also
++++++++

iaf_cond_exp, iaf_cond_alpha, iaf_cond_alpha_mc

Examples using this model
+++++++++++++++++++++++++

.. listexamples:: iaf_cond_beta

EndUserDocs */

void register_iaf_cond_beta( const std::string& name );

class iaf_cond_beta : public ArchivingNode
{

  // Boilerplate function declarations --------------------------------

public:
  iaf_cond_beta();
  iaf_cond_beta( const iaf_cond_beta& );
  ~iaf_cond_beta() override;

  /*
   * Import all overloaded virtual functions that we
   * override in this class.  For background information,
   * see http://www.gotw.ca/gotw/005.htm.
   */

  using Node::handle;
  using Node::handles_test_event;

  size_t send_test_event( Node& tagret, size_t receptor_type, synindex, bool ) override;

  size_t handles_test_event( SpikeEvent&, size_t ) override;
  size_t handles_test_event( CurrentEvent&, size_t ) override;
  size_t handles_test_event( DataLoggingRequest&, size_t ) override;

  void handle( SpikeEvent& ) override;
  void handle( CurrentEvent& ) override;
  void handle( DataLoggingRequest& ) override;

  void get_status( DictionaryDatum& ) const override;
  void set_status( const DictionaryDatum& ) override;

private:
  void init_buffers_() override;
  double get_normalisation_factor( double, double );
  void pre_run_hook() override;
  void update( Time const&, const long, const long ) override;

  // END Boilerplate function declarations ----------------------------

  // Friends --------------------------------------------------------

  // make dynamics function quasi-member
  friend int iaf_cond_beta_dynamics( double, const double*, double*, void* );

  // The next two classes need to be friends to access the State_ class/member
  friend class RecordablesMap< iaf_cond_beta >;
  friend class UniversalDataLogger< iaf_cond_beta >;

private:
  // Parameters class -------------------------------------------------

  //! Model parameters
  struct Parameters_
  {
    double V_th;         //!< Threshold Potential in mV
    double V_reset;      //!< Reset Potential in mV
    double t_ref;        //!< Refractory period in ms
    double g_L;          //!< Leak Conductance in nS
    double C_m;          //!< Membrane Capacitance in pF
    double E_ex;         //!< Excitatory reversal Potential in mV
    double E_in;         //!< Inhibitory reversal Potential in mV
    double E_L;          //!< Leak reversal Potential (resting potential) in mV
    double tau_rise_ex;  //!< Excitatory Synaptic Rise Time Constant in ms
    double tau_decay_ex; //!< Excitatory Synaptic Decay Time Constant in ms
    double tau_rise_in;  //!< Inhibitory Synaptic Rise Time Constant in ms
    double tau_decay_in; //!< Inhibitory Synaptic Decay Time Constant  in ms
    double I_e;          //!< Constant Current in pA

    Parameters_(); //!< Set default parameter values

    void get( DictionaryDatum& ) const;             //!< Store current values in dictionary
    void set( const DictionaryDatum&, Node* node ); //!< Set values from dictionary
  };

  // State variables class --------------------------------------------

  /**
   * State variables of the model.
   *
   * State variables consist of the state vector for the subthreshold
   * dynamics and the refractory count. The state vector must be a
   * C-style array to be compatible with GSL ODE solvers.
   *
   * @note Copy constructor required because of the C-style array.
   */
public:
  struct State_
  {
    //! Symbolic indices to the elements of the state vector y
    enum StateVecElems
    {
      V_M = 0,
      DG_EXC,
      G_EXC,
      DG_INH,
      G_INH,
      STATE_VEC_SIZE
    };

    //! state vector, must be C-array for GSL solver
    double y[ STATE_VEC_SIZE ];

    //!< number of refractory steps remaining
    int r;

    State_( const Parameters_& ); //!< Default initialization
    State_( const State_& );

    State_& operator=( const State_& );

    void get( DictionaryDatum& ) const; //!< Store current values in dictionary

    /**
     * Set state from values in dictionary.
     * Requires Parameters_ as argument to, eg, check bounds.'
     */
    void set( const DictionaryDatum&, const Parameters_&, Node* );
  };

private:
  // Buffers class --------------------------------------------------------

  /**
   * Buffers of the model.
   * Buffers are on par with state variables in terms of persistence,
   * i.e., initalized only upon first Simulate call after ResetKernel,
   * but are implementation details hidden from the user.
   */
  struct Buffers_
  {
    Buffers_( iaf_cond_beta& );                  //!< Sets buffer pointers to 0
    Buffers_( const Buffers_&, iaf_cond_beta& ); //!< Sets buffer pointers to 0

    //! Logger for all analog data
    UniversalDataLogger< iaf_cond_beta > logger_;

    /** buffers and sums up incoming spikes/currents */
    RingBuffer spike_exc_;
    RingBuffer spike_inh_;
    RingBuffer currents_;

    /* GSL ODE stuff */
    gsl_odeiv_step* s_;    //!< stepping function
    gsl_odeiv_control* c_; //!< adaptive stepsize control function
    gsl_odeiv_evolve* e_;  //!< evolution function
    gsl_odeiv_system sys_; //!< struct describing system

    // Since IntegrationStep_ is initialized with step_, and the resolution
    // cannot change after nodes have been created, it is safe to place both
    // here.
    double step_;            //!< step size in ms
    double IntegrationStep_; //!< current integration time step, updated by GSL

    /**
     * Input current injected by CurrentEvent.
     * This variable is used to transport the current applied into the
     * _dynamics function computing the derivative of the state vector.
     * It must be a part of Buffers_, since it is initialized once before
     * the first simulation, but not modified before later Simulate calls.
     */
    double I_stim_;
  };

  // Variables class -------------------------------------------------------

  /**
   * Internal variables of the model.
   * Variables are re-initialized upon each call to Simulate.
   */
  struct Variables_
  {
    /**
     * Impulse to add to DG_EXC on spike arrival to evoke unit-amplitude
     * conductance excursion.
     */
    double PSConInit_E;

    /**
     * Impulse to add to DG_INH on spike arrival to evoke unit-amplitude
     * conductance excursion.
     */
    double PSConInit_I;

    //! refractory time in steps
    int RefractoryCounts;
  };

  // Access functions for UniversalDataLogger -------------------------------

  //! Read out state vector elements, used by UniversalDataLogger
  template < State_::StateVecElems elem >
  double
  get_y_elem_() const
  {
    return S_.y[ elem ];
  }

  //! Read out remaining refractory time, used by UniversalDataLogger
  double
  get_r_() const
  {
    return Time::get_resolution().get_ms() * S_.r;
  }

  // Data members -----------------------------------------------------------

  // keep the order of these lines, seems to give best performance
  Parameters_ P_;
  State_ S_;
  Variables_ V_;
  Buffers_ B_;

  //! Mapping of recordables names to access functions
  static RecordablesMap< iaf_cond_beta > recordablesMap_;
};


// Boilerplate inline function definitions ----------------------------------

inline size_t
iaf_cond_beta::send_test_event( Node& target, size_t receptor_type, synindex, bool )
{
  SpikeEvent e;
  e.set_sender( *this );
  return target.handles_test_event( e, receptor_type );
}

inline size_t
iaf_cond_beta::handles_test_event( SpikeEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
iaf_cond_beta::handles_test_event( CurrentEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
iaf_cond_beta::handles_test_event( DataLoggingRequest& dlr, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return B_.logger_.connect_logging_device( dlr, recordablesMap_ );
}

inline void
iaf_cond_beta::get_status( DictionaryDatum& d ) const
{
  P_.get( d );
  S_.get( d );
  ArchivingNode::get_status( d );

  ( *d )[ names::recordables ] = recordablesMap_.get_list();
}

inline void
iaf_cond_beta::set_status( const DictionaryDatum& d )
{
  Parameters_ ptmp = P_;     // temporary copy in case of errors
  ptmp.set( d, this );       // throws if BadProperty
  State_ stmp = S_;          // temporary copy in case of errors
  stmp.set( d, ptmp, this ); // throws if BadProperty

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  ArchivingNode::set_status( d );

  // if we get here, temporaries contain consistent set of properties
  P_ = ptmp;
  S_ = stmp;
}

} // namespace

#endif // HAVE_GSL

#endif // IAF_COND_BETA_H
