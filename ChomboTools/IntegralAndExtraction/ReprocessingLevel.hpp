/* GRChombo
 * Copyright 2012 The GRChombo collaboration.
 * Please refer to LICENSE in GRChombo's root directory.
 */

#ifndef REPROCESSINGLEVEL_HPP_
#define REPROCESSINGLEVEL_HPP_

#include "AMRReductions.hpp"
#include "BoxLoops.hpp"
#include "ExcisionDiagnostics.hpp"
#include "ForceExtraction.hpp"
#include "GRAMRLevel.hpp"
#include "SmallDataIO.hpp"

class ReprocessingLevel : public GRAMRLevel
{
    friend class DefaultLevelFactory<ReprocessingLevel>;
    // Inherit the contructors from GRAMRLevel
    using GRAMRLevel::GRAMRLevel;

    // initialize data
    virtual void initialData() { m_state_new.setVal(0.); }

    void postRestart()
    {
        // Add code here to do what you need it to do on each level
        // Note that if you want the AMRInterpolator you need to define it
        // and set it here (currently it is just a nullptr)
        pout() << "The time is " << m_time << " on level " << m_level
               << ". Your wish is my command." << endl;

        // calculate the density of the PF, but excise the BH region completely
        fillAllGhosts();
        // excise within horizon
        BoxLoops::loop(
            ExcisionDiagnostics(m_dx, m_p.center, m_p.inner_r, m_p.outer_r),
            m_state_new, m_state_new, SKIP_GHOST_CELLS, disable_simd());

        // write out the integral after each coarse timestep
        if (m_level == m_p.max_level)
        {
            // integrate the densities and write to a file
            AMRReductions<VariableType::evolution> amr_reductions(m_gr_amr);
            double source_sum = amr_reductions.sum(c_Source);
            double rho_sum = amr_reductions.sum(c_rho);

            SmallDataIO integral_file("IntegralData", m_dt, m_time,
                                      m_restart_time, SmallDataIO::APPEND,
                                      false);
            // remove any duplicate data if this is post restart
            integral_file.remove_duplicate_time_data();
            std::vector<double> data_for_writing = {source_sum, rho_sum};
            // write data
            if (m_time == 0.0)
            {
                integral_file.write_header_line({"Source", "rho"});
            }
            integral_file.write_time_data_line(data_for_writing);

            // Now refresh the interpolator and do the interpolation
            // set up an interpolator
            // pass the boundary params so that we can use symmetries if
            // applicable
//            AMRInterpolator<Lagrange<4>> interpolator(
//                m_gr_amr, m_p.origin, m_p.dx, m_p.boundary_params,
//                m_p.verbosity);

            // this should fill all ghosts including the boundary ones according
            // to the conditions set in params.txt
//            interpolator.refresh();
//            ForceExtraction my_extraction(m_p.extraction_params, m_dt, m_time,
//                                          m_restart_time);
//            my_extraction.execute_query(&interpolator);
        }
    }

    virtual void specificEvalRHS(GRLevelData &a_soln, GRLevelData &a_rhs,
                                 const double a_time)
    {
    }

    virtual void computeTaggingCriterion(FArrayBox &tagging_criterion,
                                         const FArrayBox &current_state){};
};

#endif /* REPROCESSINGLEVEL_HPP_ */
