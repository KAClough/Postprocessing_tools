/* GRChombo
 * Copyright 2012 The GRChombo collaboration.
 * Please refer to LICENSE in GRChombo's root directory.
 */

#ifndef SIMULATIONPARAMETERS_HPP_
#define SIMULATIONPARAMETERS_HPP_

// General includes
#include "ChomboParameters.hpp"
#include "GRParmParse.hpp"
#include "SphericalExtraction.hpp"

class SimulationParameters : public ChomboParameters {
public:
  // For the Interpolator test we don't need many parameters
  SimulationParameters(GRParmParse &pp) : ChomboParameters(pp) {
    // read the problem specific params
    readParams(pp);
  }

  void readParams(GRParmParse &pp) {
    // Grid setup
    pp.get("num_files", num_files);
    pp.get("start_file", start_file);
    pp.get("checkpoint_interval", checkpoint_interval);

    // Extraction params
    pp.load("inner_r", inner_r, 5.0);
    pp.load("outer_r", outer_r, 100.0);

    // Extraction params
    pp.load("num_extraction_radii", extraction_params.num_extraction_radii, 2);
    // Check for multiple extraction radii, otherwise load single
    // radius/level (for backwards compatibility).
    extraction_params.extraction_levels = {0, 0};
    extraction_params.extraction_radii = {inner_r, outer_r};
    pp.load("num_points_phi", extraction_params.num_points_phi, 2);
    pp.load("num_points_theta", extraction_params.num_points_theta, 5);
    if (extraction_params.num_points_theta % 2 == 0) {
      extraction_params.num_points_theta += 1;
      pout() << "Parameter: num_points_theta incompatible with Simpson's "
             << "rule so increased by 1.\n";
    }
    pp.load("extraction_center", extraction_params.center, center);
    pp.load("write_extraction", extraction_params.write_extraction, false);
  }

  SphericalExtraction::params_t extraction_params;
  double inner_r, outer_r;
  int num_files, start_file, checkpoint_interval;
};

#endif /* SIMULATIONPARAMETERS_HPP_ */
