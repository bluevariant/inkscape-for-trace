/**
 * \file
 * \brief PathVectorSatellites a class to manage satellites -per node extra data- in a pathvector
 */ /*
    * Authors:
    * Jabiertxof
    * Nathan Hurst
    * Johan Engelen
    * Josh Andler
    * suv
    * Mc-
    * Liam P. White
    * Krzysztof Kosiński
    * This code is in public domain
    */

#include <helper/geom-pathvectorsatellites.h>
Geom::PathVector PathVectorSatellites::getPathVector() const
{
    return _pathvector;
}

void PathVectorSatellites::setPathVector(Geom::PathVector pathv)
{
    _pathvector = pathv;
}

Satellites PathVectorSatellites::getSatellites()
{
    return _satellites;
}

void PathVectorSatellites::setSatellites(Satellites satellites)
{
    _satellites = satellites;
}

size_t PathVectorSatellites::getTotalSatellites()
{
    size_t counter = 0;
    for (size_t i = 0; i < _satellites.size(); ++i) {
        for (size_t j = 0; j < _satellites[i].size(); ++j) {
            counter++;
        }
    }
    return counter;
}

std::pair<size_t, size_t> PathVectorSatellites::getIndexData(size_t index)
{
    size_t counter = 0;
    for (size_t i = 0; i < _satellites.size(); ++i) {
        for (size_t j = 0; j < _satellites[i].size(); ++j) {
            if (index == counter) {
                return std::make_pair(i,j);
            }
            counter++;
        }
    }
    return std::make_pair(0,0);
}

void PathVectorSatellites::setSelected(std::vector<size_t> selected)
{
    size_t counter = 0;
    for (size_t i = 0; i < _satellites.size(); ++i) {
        for (size_t j = 0; j < _satellites[i].size(); ++j) {
            if(find (selected.begin(), selected.end(), counter) != selected.end()){
                _satellites[i][j].setSelected(true);
            } else {
                _satellites[i][j].setSelected(false);
            }
            counter++;
        }
    }
}

void PathVectorSatellites::updateSteps(size_t steps, bool apply_no_radius, bool apply_with_radius, bool only_selected)
{
    for (size_t i = 0; i < _satellites.size(); ++i) {
        for (size_t j = 0; j < _satellites[i].size(); ++j) {
            if ((!apply_no_radius && _satellites[i][j].amount == 0) ||
                (!apply_with_radius && _satellites[i][j].amount != 0)) 
            {
                continue;
            }
            if (only_selected) {
                if (_satellites[i][j].selected) {
                    _satellites[i][j].steps = steps;
                }
            } else {
                _satellites[i][j].steps = steps;
            }
        }
    }
}

void PathVectorSatellites::updateAmount(double radius, bool apply_no_radius, bool apply_with_radius, bool only_selected, 
                                         bool use_knot_distance, bool flexible)
{
    double power = 0;
    if (!flexible) {
        power = radius;
    } else {
        power = radius / 100;
    }
    for (size_t i = 0; i < _satellites.size(); ++i) {
        for (size_t j = 0; j < _satellites[i].size(); ++j) {
            boost::optional<size_t> previous_index = boost::none;
            if(j == 0 && _pathvector[i].closed()){
                previous_index = _pathvector[i].size() - 1;
            } else if(!_pathvector[i].closed() || j != 0) {
                previous_index = j - 1;
            }
            if (!_pathvector[i].closed() && j == 0) {
                _satellites[i][j].amount = 0;
                continue;
            }
            if (_pathvector[i].size() == j) {
                continue;
            }
            if ((!apply_no_radius && _satellites[i][j].amount == 0) ||
                (!apply_with_radius && _satellites[i][j].amount != 0)) 
            {
                continue;
            }
            
            Geom::Point satellite_point = _pathvector[i].pointAt(j);
            if (_satellites[i][j].selected || !only_selected) {
                if (!use_knot_distance && !flexible) {
                    if(previous_index) {
                        _satellites[i][j].amount = _satellites[i][j].radToLen(power, _pathvector[i][*previous_index], _pathvector[i][j]);
                    } else {
                        _satellites[i][j].amount = 0.0;
                    }
                } else {
                    _satellites[i][j].amount = power;
                }
            }
        }
    }
}

void PathVectorSatellites::updateSatelliteType(SatelliteType satellitetype, bool apply_no_radius, bool apply_with_radius,
                                               bool only_selected)
{
    for (size_t i = 0; i < _satellites.size(); ++i) {
        for (size_t j = 0; j < _satellites[i].size(); ++j) {
            if ((!apply_no_radius && _satellites[i][j].amount == 0) ||
                (!apply_with_radius && _satellites[i][j].amount != 0)) 
            {
                continue;
            }
            if (_pathvector[i].size() == j) {
                if (!only_selected) {
                    _satellites[i][j].satellite_type = satellitetype;
                }
                continue;
            }
            if (only_selected) {
                Geom::Point satellite_point = _pathvector[i].pointAt(j);
                if (_satellites[i][j].selected) {
                    _satellites[i][j].satellite_type = satellitetype;
                }
            } else {
                _satellites[i][j].satellite_type = satellitetype;
            }
        }
    }
}

void PathVectorSatellites::recalculateForNewPathVector(Geom::PathVector const pathv, Satellite const S)
{
    Satellites satellites;
    bool found = false;
    //TODO evaluate fix on nodes at same position
    size_t number_nodes = pathv.nodes().size();
    size_t previous_number_nodes = _pathvector.nodes().size();
    for (size_t i = 0; i < pathv.size(); i++) {
        std::vector<Satellite> path_satellites;
        for (size_t j = 0; j < pathv[i].size_closed(); j++) {
            found = false;
            for (size_t k = 0; k < _pathvector.size(); k++) {
                for (size_t l = 0; l < _pathvector[k].size_closed(); l++) {
                    if (Geom::are_near(_pathvector[k][l].initialPoint(),  pathv[i][j].initialPoint()))
                    {
                        path_satellites.push_back(_satellites[k][l]);
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            
            if (!found && previous_number_nodes < number_nodes) {
                path_satellites.push_back(S);
            }
        }
        satellites.push_back(path_satellites);
    }
    setPathVector(pathv);
    setSatellites(satellites);
}

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim:
// filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99
// :
