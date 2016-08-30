/*
  Copyright (C) <2016> <Alexandre Xavier Falc�o and Jo�o Paulo Papa>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  please see full copyright in COPYING file.
  -------------------------------------------------------------------------
  written by A.X. Falc�o <afalcao@ic.unicamp.br> and by J.P. Papa
  <papa.joaopaulo@gmail.com>, Aug 30th 2016

  This program is a collection of functions to manage the Optimum-Path Forest (OPF)
  classifier.*/

#include "graph.h"

/*----------- Constructor and destructor ------------------------*/
/* It allocates the graph
Parameters:
nnodes:number of samples (nodes)
nefeats: number os features (dimensionality of the feature space) */
Graph *CreateGraph(int nnodes, int nfeats){
    if(nnodes < 0 || nfeats < 0){
        
    }
}