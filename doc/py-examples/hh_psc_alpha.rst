.. note::
    :class: sphx-glr-download-link-note

    Click :ref:`here <sphx_glr_download_py-examples_hh_psc_alpha.py>` to download the full example code
.. rst-class:: sphx-glr-example-title

.. _sphx_glr_py-examples_hh_psc_alpha.py:

Example using hh_psc_alpha
-------------------------------

This example produces a rate-response (FI) curve of the Hodgkin-Huxley
neuron  in response to a range of different current (DC) stimulations.
The result is plotted using matplotlib.

Since a DC input affetcs only the neuron's channel dynamics, this routine
does not yet check correctness of synaptic response.

References
~~~~~~~~~~~

See Also
~~~~~~~~~~

:Authors:

KEYWORDS:




.. image:: /py-examples/images/sphx_glr_hh_psc_alpha_001.png
    :class: sphx-glr-single-img


.. rst-class:: sphx-glr-script-out

 Out:

 .. code-block:: none

    Simulating with current I=0 pA
    Simulating with current I=20 pA
    Simulating with current I=40 pA
    Simulating with current I=60 pA
    Simulating with current I=80 pA
    Simulating with current I=100 pA
    Simulating with current I=120 pA
    Simulating with current I=140 pA
    Simulating with current I=160 pA
    Simulating with current I=180 pA
    Simulating with current I=200 pA
    Simulating with current I=220 pA
    Simulating with current I=240 pA
    Simulating with current I=260 pA
    Simulating with current I=280 pA
    Simulating with current I=300 pA
    Simulating with current I=320 pA
    Simulating with current I=340 pA
    Simulating with current I=360 pA
    Simulating with current I=380 pA
    Simulating with current I=400 pA
    Simulating with current I=420 pA
    Simulating with current I=440 pA
    Simulating with current I=460 pA
    Simulating with current I=480 pA
    Simulating with current I=500 pA
    Simulating with current I=520 pA
    Simulating with current I=540 pA
    Simulating with current I=560 pA
    Simulating with current I=580 pA
    Simulating with current I=600 pA
    Simulating with current I=620 pA
    Simulating with current I=640 pA
    Simulating with current I=660 pA
    Simulating with current I=680 pA
    Simulating with current I=700 pA
    Simulating with current I=720 pA
    Simulating with current I=740 pA
    Simulating with current I=760 pA
    Simulating with current I=780 pA
    Simulating with current I=800 pA
    Simulating with current I=820 pA
    Simulating with current I=840 pA
    Simulating with current I=860 pA
    Simulating with current I=880 pA
    Simulating with current I=900 pA
    Simulating with current I=920 pA
    Simulating with current I=940 pA
    Simulating with current I=960 pA
    Simulating with current I=980 pA
    Simulating with current I=1000 pA
    Simulating with current I=1020 pA
    Simulating with current I=1040 pA
    Simulating with current I=1060 pA
    Simulating with current I=1080 pA
    Simulating with current I=1100 pA
    Simulating with current I=1120 pA
    Simulating with current I=1140 pA
    Simulating with current I=1160 pA
    Simulating with current I=1180 pA
    Simulating with current I=1200 pA
    Simulating with current I=1220 pA
    Simulating with current I=1240 pA
    Simulating with current I=1260 pA
    Simulating with current I=1280 pA
    Simulating with current I=1300 pA
    Simulating with current I=1320 pA
    Simulating with current I=1340 pA
    Simulating with current I=1360 pA
    Simulating with current I=1380 pA
    Simulating with current I=1400 pA
    Simulating with current I=1420 pA
    Simulating with current I=1440 pA
    Simulating with current I=1460 pA
    Simulating with current I=1480 pA
    Simulating with current I=1500 pA
    Simulating with current I=1520 pA
    Simulating with current I=1540 pA
    Simulating with current I=1560 pA
    Simulating with current I=1580 pA
    Simulating with current I=1600 pA
    Simulating with current I=1620 pA
    Simulating with current I=1640 pA
    Simulating with current I=1660 pA
    Simulating with current I=1680 pA
    Simulating with current I=1700 pA
    Simulating with current I=1720 pA
    Simulating with current I=1740 pA
    Simulating with current I=1760 pA
    Simulating with current I=1780 pA
    Simulating with current I=1800 pA
    Simulating with current I=1820 pA
    Simulating with current I=1840 pA
    Simulating with current I=1860 pA
    Simulating with current I=1880 pA
    Simulating with current I=1900 pA
    Simulating with current I=1920 pA
    Simulating with current I=1940 pA
    Simulating with current I=1960 pA
    Simulating with current I=1980 pA




|


.. code-block:: python
   :lineno-start: 43


    import nest
    import numpy as np
    import matplotlib.pyplot as plt

    nest.set_verbosity('M_WARNING')
    nest.ResetKernel()

    simtime = 1000

    # Amplitude range, in pA
    dcfrom = 0
    dcstep = 20
    dcto = 2000

    h = 0.1  # simulation step size in mS

    neuron = nest.Create('hh_psc_alpha')
    sd = nest.Create('spike_detector')

    nest.SetStatus(sd, {'to_memory': False})

    nest.Connect(neuron, sd, syn_spec={'weight': 1.0, 'delay': h})

    # Simulation loop
    n_data = int(dcto / float(dcstep))
    amplitudes = np.zeros(n_data)
    event_freqs = np.zeros(n_data)
    for i, amp in enumerate(range(dcfrom, dcto, dcstep)):
        nest.SetStatus(neuron, {'I_e': float(amp)})
        print("Simulating with current I={} pA".format(amp))
        nest.Simulate(1000)  # one second warm-up time for equilibrium state
        nest.SetStatus(sd, {'n_events': 0})  # then reset spike counts
        nest.Simulate(simtime)  # another simulation call to record firing rate

        n_events = nest.GetStatus(sd, keys={'n_events'})[0][0]
        amplitudes[i] = amp
        event_freqs[i] = n_events / (simtime / 1000.)

    plt.plot(amplitudes, event_freqs)
    plt.show()

**Total running time of the script:** ( 0 minutes  4.585 seconds)


.. _sphx_glr_download_py-examples_hh_psc_alpha.py:


.. only :: html

 .. container:: sphx-glr-footer
    :class: sphx-glr-footer-example



  .. container:: sphx-glr-download

     :download:`Download Python source code: hh_psc_alpha.py <hh_psc_alpha.py>`



  .. container:: sphx-glr-download

     :download:`Download Jupyter notebook: hh_psc_alpha.ipynb <hh_psc_alpha.ipynb>`


.. only:: html

 .. rst-class:: sphx-glr-signature

    `Gallery generated by Sphinx-Gallery <https://sphinx-gallery.readthedocs.io>`_
