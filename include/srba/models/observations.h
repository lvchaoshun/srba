/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2015, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#pragma once

#include <mrpt/utils/TCamera.h>
#include <mrpt/utils/TStereoCamera.h>

namespace srba {
namespace observations {

	/** \defgroup mrpt_srba_observations Observation types
		* \ingroup mrpt_srba_grp */

	/** \addtogroup mrpt_srba_observations
		* @{ */

	/** Observation = one monocular camera feature (the coordinates of one pixel) */
	struct MonocularCamera
	{
		static const size_t  OBS_DIMS = 2; //!< Each observation is one pixel (px,py) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			mrpt::utils::TPixelCoordf  px;

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0] = px.x;
				obs[1] = px.y;
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			mrpt::utils::TCamera  camera_calib;
		};
	};

	/** Landmark matcher overloaded function (used to provide a first initial guess for the relative pose in loop closures) (made a template just to avoid link errors due to .h implementation) */
	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<MonocularCamera::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<MonocularCamera::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		return false; // We cannot find any absolute relative pose only from 2 sets of monocular features, right?
	}

	// -------------------------------------------------------------------------------------------------

	/** Observation = one stereo camera feature (the coordinates of two pixels) */
	struct StereoCamera
	{
		static const size_t  OBS_DIMS = 4; //!< Each observation is a pair of pixels (px_l,py_l,px_r,py_r) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			mrpt::utils::TPixelCoordf  left_px, right_px;

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0] = left_px.x;  obs[1] = left_px.y;
				obs[2] = right_px.x; obs[3] = right_px.y;
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			mrpt::utils::TStereoCamera camera_calib;
		};
	};

	/** Landmark matcher overloaded function (used to provide a first initial guess for the relative pose in loop closures) (made a template just to avoid link errors due to .h implementation) */
	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<StereoCamera::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<StereoCamera::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (POSE::rotation_dimensions==3 && new_kf_obs.size()<3) return false; // Minimum number of points for SE(3): 3
		if (POSE::rotation_dimensions==2 && new_kf_obs.size()<2) return false; // Minimum number of points for SE(2): 2
		MRPT_TODO("Implement!")
		return true;
	}

	// -------------------------------------------------------------------------------------------------

	/** Observation = XYZ coordinates of landmarks relative to the sensor */
	struct Cartesian_3D
	{
		static const size_t  OBS_DIMS = 3; //!< Each observation is a triplet of coordinates (x,y,z) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			mrpt::math::TPoint3D  pt;

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0] = pt.x; obs[1] = pt.y; obs[2] = pt.z; 
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			// This type of observations has no further parameters.
		};
	};

	/** Landmark matcher overloaded function (used to provide a first initial guess for the relative pose in loop closures) (made a template just to avoid link errors due to .h implementation) */
	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<Cartesian_3D::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<Cartesian_3D::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (POSE::rotation_dimensions==3 && new_kf_obs.size()<3) return false; // Minimum number of points for SE(3): 3
		if (POSE::rotation_dimensions==2 && new_kf_obs.size()<2) return false; // Minimum number of points for SE(2): 2
		MRPT_TODO("Implement!")
		return true;
	}

	// -------------------------------------------------------------------------------------------------

	/** Observation = XY coordinates of landmarks relative to the sensor */
	struct Cartesian_2D
	{
		static const size_t  OBS_DIMS = 2; //!< Each observation is a pair of coordinates (x,y) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			mrpt::math::TPoint2D  pt;

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0] = pt.x; obs[1] = pt.y;
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			// This type of observations has no further parameters.
		};
	};

	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<Cartesian_2D::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<Cartesian_2D::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (new_kf_obs.size()<2) return false; // Minimum number of points for SE(2): 2
		MRPT_TODO("Implement!")
		return true;
	}
	// -------------------------------------------------------------------------------------------------

	/** Observation = Range+Bearing (yaw & pitch) of landmarks relative to the sensor */
	struct RangeBearing_3D
	{
		static const size_t  OBS_DIMS = 3; //!< Each observation is a triplet of coordinates (range,yaw,pitch) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			double range; //!< Distance (in meters)
			double yaw;   //!< Angle around +Z (in radians)
			double pitch; //!< Angle around +Y (in radians)

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0] = range; obs[1] = yaw; obs[2] = pitch; 
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			// This type of observations has no further parameters.
		};
	};

	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<RangeBearing_3D::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<RangeBearing_3D::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (POSE::rotation_dimensions==3 && new_kf_obs.size()<3) return false; // Minimum number of points for SE(3): 3
		if (POSE::rotation_dimensions==2 && new_kf_obs.size()<2) return false; // Minimum number of points for SE(2): 2
		MRPT_TODO("Implement!")
		return true;
	}
	// -------------------------------------------------------------------------------------------------

	/** Observation = Range+Bearing (yaw) of landmarks relative to the sensor, for planar environments only. */
	struct RangeBearing_2D
	{
		static const size_t  OBS_DIMS = 2; //!< Each observation is a pair of coordinates (range,yaw) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			double range; //!< Distance (in meters)
			double yaw;   //!< Angle around +Z (in radians)

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0] = range; obs[1] = yaw;
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			// This type of observations has no further parameters.
		};
	};

	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<RangeBearing_2D::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<RangeBearing_2D::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (new_kf_obs.size()<2) return false; // Minimum number of points for SE(2): 2
		MRPT_TODO("Implement!")
		return true;
	}

	// -------------------------------------------------------------------------------------------------

	/** Observation = Relative SE(2) poses (x,y,yaw) */
	struct RelativePoses_2D
	{
		static const size_t  OBS_DIMS = 3; //!< Each observation is a triplet (x,y,yaw) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			double x,y;   //!< Displacement (in meters)
			double yaw;   //!< Angle around +Z (in radians)

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0]=x; obs[1]=y; obs[2]=yaw;
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			// This type of observations has no further parameters.
		};
	};

	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<RelativePoses_2D::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<RelativePoses_2D::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (new_kf_obs.size()<2) return false;
		MRPT_TODO("Implement!")
		return true;
	}

	// -------------------------------------------------------------------------------------------------

	/** Observation = Relative SE(3) poses (x,y,z,yaw,pitch,roll) */
	struct RelativePoses_3D
	{
		static const size_t  OBS_DIMS = 6; //!< Each observation is a vector (x,y,z,yaw,pitch,roll) 
		
		/** The observation-specific data structure */
		struct obs_data_t
		{
			double x,y,z;   //!< Displacement (in meters)
			double yaw,pitch,roll;   //!< Angles (in radians)

			/** Converts this observation into a plain array of its parameters */
			template <class ARRAY>
			inline void getAsArray(ARRAY &obs) const {
				obs[0]=x; obs[1]=y; obs[2]=z; 
				obs[3]=yaw; obs[4]=pitch; obs[5]=roll;
			}
		};

		/** The type "TObservationParams" must be declared in each "observations::TYPE" to 
		  *  hold sensor-specific parameters, etc. needed in the sensor model. */
		struct TObservationParams
		{
			// This type of observations has no further parameters.
		};
	};

	template <class OBS_T,class POSE>
	bool landmark_matcher_find_relative_pose(
		const mrpt::aligned_containers<RelativePoses_3D::obs_data_t>::vector_t & new_kf_obs,
		const mrpt::aligned_containers<RelativePoses_3D::obs_data_t>::vector_t & old_kf_obs,
		POSE &pose_new_kf_wrt_old_kf)
	{
		ASSERT_(new_kf_obs.size()==old_kf_obs.size())
		if (new_kf_obs.size()<2) return false;
		MRPT_TODO("Implement!")
		return true;
	}
	// -------------------------------------------------------------------------------------------------

	/** @} */

}
} // end NS
