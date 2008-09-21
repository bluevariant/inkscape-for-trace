#ifndef SEEN_SNAPPEDPOINT_H
#define SEEN_SNAPPEDPOINT_H

/**
 *    \file src/snapped-point.h
 *    \brief SnappedPoint class.
 *
 *    Authors:
 *      Mathieu Dimanche <mdimanche@free.fr>
 *      Diederik van Lierop <mail@diedenrezi.nl>
 *
 *    Released under GNU GPL, read the file 'COPYING' for more information.
 */

#include <vector>
#include <list>
#include "libnr/nr-coord.h"
#include "libnr/nr-point.h"
#include <libnr/nr-values.h>

namespace Inkscape
{

enum SnapTargetType {
    SNAPTARGET_UNDEFINED,
    SNAPTARGET_GRID,
    SNAPTARGET_GRID_INTERSECTION,
    SNAPTARGET_GUIDE,
    SNAPTARGET_GUIDE_INTERSECTION,
    SNAPTARGET_GRID_GUIDE_INTERSECTION,
    SNAPTARGET_NODE,
    SNAPTARGET_PATH,
    SNAPTARGET_PATH_INTERSECTION,
    SNAPTARGET_BBOX_CORNER,
    SNAPTARGET_BBOX_EDGE,
    SNAPTARGET_GRADIENT
};
    
/// Class describing the result of an attempt to snap.
class SnappedPoint
{

public:
    SnappedPoint();
    SnappedPoint(Geom::Point const &p, SnapTargetType const &target, Geom::Coord const &d, Geom::Coord const &t, bool const &a, bool const &at_intersection, bool const &fully_constrained, Geom::Coord const &d2, Geom::Coord const &t2, bool const &a2);
    SnappedPoint(Geom::Point const &p, SnapTargetType const &target, Geom::Coord const &d, Geom::Coord const &t, bool const &a, bool const &fully_constrained);
    ~SnappedPoint();

    Geom::Coord getDistance() const;
    void setDistance(Geom::Coord const d) {_distance = d;}
    Geom::Coord getTolerance() const;
    bool getAlwaysSnap() const;
    Geom::Coord getSecondDistance() const;
    void setSecondDistance(Geom::Coord const d) {_second_distance = d;}
    Geom::Coord getSecondTolerance() const;
    bool getSecondAlwaysSnap() const;
    
    /* This is the preferred method to find out which point we have snapped
     * to, because it only returns a point if snapping has actually occured
     * (by overwriting p)
     */ 
    void getPoint(Geom::Point &p) const;
    
    /* This method however always returns a point, even if no snapping
     * has occured; A check should be implemented in the calling code
     * to check for snapping. Use this method only when really needed, e.g.
     * when the calling code is trying to snap multiple points and must
     * determine itself which point is most appropriate
     */  
    Geom::Point getPoint() const {return _point;}
     
    bool getAtIntersection() const {return _at_intersection;}
    bool getFullyConstrained() const {return _fully_constrained;}        
    bool getSnapped() const {return _distance < NR_HUGE;}
    Geom::Point getTransformation() const {return _transformation;}
    void setTransformation(Geom::Point const t) {_transformation = t;}
    void setTarget(SnapTargetType const target) {_target = target;}
    SnapTargetType getTarget() {return _target;}
    
    bool isOtherOneBetter(SnappedPoint const &other_one) const;
    
protected:
    Geom::Point _point; // Location of the snapped point
    SnapTargetType _target; // Describes to what we've snapped to
    bool _at_intersection; // If true, the snapped point is at an intersection
    bool _fully_constrained; // When snapping for example to a node, then the snap will be "fully constrained". 
                            // When snapping to a line however, the snap is only partly constrained (i.e. only in one dimension)
    
    /* Distance from original point to snapped point. If the snapped point is at
       an intersection of e.g. two lines, then this is the distance to the closest
       line */    
    Geom::Coord _distance; 
    /* The snapping tolerance in screen pixels (depends on zoom)*/  
    Geom::Coord _tolerance;
    /* If true then "Always snap" is on */
    bool _always_snap;
    
    /* If the snapped point is at an intersection of e.g. two lines, then this is
       the distance to the fartest line */    
    Geom::Coord _second_distance;
    /* The snapping tolerance in screen pixels (depends on zoom)*/
    Geom::Coord _second_tolerance;
    /* If true then "Always snap" is on */
    bool _second_always_snap;
    /* The transformation (translation, scale, skew, or stretch) from the original point to the snapped point */
    Geom::Point _transformation;
};    

}

bool getClosestSP(std::list<Inkscape::SnappedPoint> &list, Inkscape::SnappedPoint &result);


#endif /* !SEEN_SNAPPEDPOINT_H */

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
