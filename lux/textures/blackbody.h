/***************************************************************************
 *   Copyright (C) 1998-2013 by authors (see AUTHORS.txt)                  *
 *                                                                         *
 *   This file is part of LuxRender.                                       *
 *                                                                         *
 *   Lux Renderer is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Lux Renderer is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *   This project is based on PBRT ; see http://www.pbrt.org               *
 *   Lux Renderer website : http://www.luxrender.net                       *
 ***************************************************************************/

#include "luxrays/core/color/swcspectrum.h"
#include "luxrays/core/color/spds/blackbodyspd.h"
using luxrays::BlackbodySPD;

#include "lux.h"
#include "texture.h"
#include "paramset.h"

namespace lux
{

// BlackBodyTexture Declarations
class BlackBodyTexture : public Texture<SWCSpectrum> {
public:
	// BlackBodyTexture Public Methods
	BlackBodyTexture(float t) : Texture("BlackBodyTexture-" + boost::lexical_cast<string>(this)),
			BBSPD(t) { }
	virtual ~BlackBodyTexture() { }
	virtual SWCSpectrum Evaluate(const SpectrumWavelengths &sw,
		const DifferentialGeometry &) const {
		return SWCSpectrum(sw, BBSPD);
	}
	virtual float Y() const { return BBSPD.Y(); }
	virtual float Filter() const { return BBSPD.Filter(); }
	virtual void GetDuv(const SpectrumWavelengths &sw,
		const DifferentialGeometry &dg, float delta,
		float *du, float *dv) const { *du = *dv = 0.f; }

	BlackbodySPD *GetBlackBodySPD() { return &BBSPD; }

	static Texture<SWCSpectrum> *CreateSWCSpectrumTexture(const Transform &tex2world, const ParamSet &tp);

private:
	BlackbodySPD BBSPD;
};

}//namespace lux

