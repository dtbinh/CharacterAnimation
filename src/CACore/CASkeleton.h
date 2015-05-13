
#ifndef __CASkeleton_H__
#define __CASkeleton_H__

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>

#include <BVH.h>

namespace chara {


/*
	
class CAJoint
{
public:
   int m_fatherId;        // Le numéro du père dans le tableau de CAJoint de CASkeleton
   Mat4f m_local2world;   // La matrice passant du repère de l'articulation vers le monde. On peut aussi stocker un quaternion + une translation
   //Mat4f m_world2local;   // Si besoin : La matrice passant du repère du monde vers l'articulation
};


class CASkeleton
{
public:
   //! Créer un squelette ayant la même structure que définit dans le BVH
   CASkeleton(const BVH& );

   //! Positionne ce squelette dans la position n du BVH
   void setPose(const BVH& bvh, const int frameNumber);

   //! Calcule la distance entre deux postures
   //! precond: les deux squelettes doivent avoir le 
   //! même nombre d'articulations (même structure d'arbre)
   float distance(const CASkeleton& skel) const;

   //! Affiche en OpenGL le squelette, les liens entre les articulations
   //! sont donnés par le champ m_fatherId de CAJoint
   void drawGL() const;

private:
   //! L'ensemble des articulations.
   //! Remarque : la notion de hiérarchie (arbre) n'est plus nécessaire ici,
   //! pour tracer les os on utilise l'information "fatherID" de la class CAJoint
   std::vector<CAJoint> m_joint;
};

*/

} // namespace

#endif //
