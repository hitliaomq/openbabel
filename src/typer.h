/**********************************************************************
typer.h - Open Babel atom typer.
 
Copyright (C) 1998-2001 by OpenEye Scientific Software, Inc.
Some portions Copyright (C) 2001-2005 by Geoffrey R. Hutchison
 
This file is part of the Open Babel project.
For more information, see <http://openbabel.sourceforge.net/>
 
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
***********************************************************************/

#ifndef OB_TYPER_H
#define OB_TYPER_H

#include "parsmart.h"
#include "data.h"

namespace OpenBabel
{

// class introduction in typer.cpp
class OBAtomTyper : public OBGlobalDataBase
{
  //    int                                                      _rc;
  std::vector<std::vector<int> >                           _mlist; //!< match list for atom typing
  std::vector<std::pair<OBSmartsPattern*,int> >            _vinthyb; //!< internal hybridization rules
  std::vector<std::pair<OBSmartsPattern*,int> >            _vimpval; //!< internal implicit valence rules
  std::vector<std::pair<OBSmartsPattern*,std::string> >    _vexttyp; //!< external atom type rules

public:
    OBAtomTyper();
    ~OBAtomTyper();

    void ParseLine(const char*);
    //! Assign atomic hybridization (1 = sp, 2 = sp2, 3 = sp3...)
    void AssignHyb(OBMol&);
    //! Assign external atomic types (i.e., EXTTYP lines in atomtyp.txt)
    void AssignTypes(OBMol&);
    //! Assign implicit valence (i.e., given an atomic type, what is the 
    //! expected number of bonds to this atom
    void AssignImplicitValence(OBMol&);
    //! Correct typing, valence, and hybridization for aromatic nitrogen atoms
    void CorrectAromaticNitrogens(OBMol&);
};

// class introduction in typer.cpp
class OBAromaticTyper : public OBGlobalDataBase
{
    std::vector<bool>             _vpa;   //!< potentially aromatic atoms
    std::vector<bool>             _visit;
    std::vector<bool>             _root;
    std::vector<std::vector<int> >     _mlist;
    std::vector<OBSmartsPattern*> _vsp;   //!< SMARTS of potentially aromatic atoms
    std::vector<std::pair<int,int> >   _verange; //!< min and max number of electrons
    std::vector<std::pair<int,int> >   _velec;   //!< # electrons an atom contributes
public:
    OBAromaticTyper();
    ~OBAromaticTyper();

    void ParseLine(const char*);
    void AssignAromaticFlags(OBMol &);
    void PropagatePotentialAromatic(OBAtom*);
    void SelectRootAtoms(OBMol &, bool avoidInnerRingAtoms = true);
    void ExcludeSmallRing(OBMol &);
    void CheckAromaticity(OBAtom*,int);
    bool TraverseCycle(OBAtom*,OBAtom*,OBBond*,std::pair<int,int>&,int);
};

}

#endif // OB_TYPER_H
