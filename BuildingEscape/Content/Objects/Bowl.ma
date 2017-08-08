//Maya ASCII 2014 scene
//Name: Bowl.ma
//Last modified: Mon, Aug 07, 2017 06:49:09 PM
//Codeset: UTF-8
requires maya "2014";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2014";
fileInfo "version" "2014";
fileInfo "cutIdentifier" "201310090405-890429";
fileInfo "osv" "Mac OS X 10.9.3";
fileInfo "license" "student";
createNode transform -n "curve1";
createNode nurbsCurve -n "curveShape1" -p "curve1";
	setAttr -k off ".v";
	setAttr ".cc" -type "nurbsCurve" 
		3 24 0 no 3
		29 0 0 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 24
		 24
		27
		0.045158523202003302 0 0
		-1.894906259195223 0.10383047995590218 0
		-2.4919315189416631 0.233618579900781 0
		-2.9072534387652733 0.33744905985668316 0
		-3.0889567786881029 0.49319477979053716 0
		-3.3744905985668354 0.70085573970234294 0
		-3.6859820384345432 0.93447431960312399 0
		-3.8417277583683975 1.2978809994487823 0
		-3.9715158583132757 1.7651181592503442 0
		-4.0234310982912271 2.2583129390408829 0
		-3.9479439405528032 2.3328759648721111 0
		-3.8043823427145198 2.2790403656827549 0
		-3.7505467435251627 2.0636979689253292 0
		-3.6428755451464503 1.6868487745998342 0
		-3.5172591470379522 1.399725578923267 0
		-3.3019167502805264 1.1305475829764848 0
		-3.0865743535231012 0.91520518621905922 0
		-2.7815059581167478 0.73575318892120378 0
		-2.440547163250824 0.59219159108292063 0
		-2.1354787678444707 0.46657519297442268 0
		-1.8304103724381182 0.44862999324463654 0
		-1.4715063778424085 0.37684919432549496 0
		-1.0228763845977717 0.34095879486592368 0
		-0.610136790812706 0.32301359513613853 0
		-0.35890399459570954 0.30506839540635339 0
		-0.14356159783828409 0.30506839540635339 0
		-0.017945199729785869 0.30506839540635339 0
		;
createNode transform -n "revolvedSurface1";
createNode nurbsSurface -n "revolvedSurfaceShape1" -p "revolvedSurface1";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".tw" yes;
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".dvu" 0;
	setAttr ".dvv" 0;
	setAttr ".cpr" 4;
	setAttr ".cps" 4;
createNode revolve -n "revolve1";
	setAttr ".ax" -type "double3" 0 1 0 ;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultShaderList1;
	setAttr -s 2 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :renderGlobalsList1;
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 18 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surfaces" "Particles" "Fluids" "Image Planes" "UI:" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 18 0 1 1 1 1 1
		 1 0 0 0 0 0 0 0 0 0 0 0 ;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "revolve1.os" "revolvedSurfaceShape1.cr";
connectAttr "curveShape1.ws" "revolve1.ic";
connectAttr "revolvedSurfaceShape1.iog" ":initialShadingGroup.dsm" -na;
// End of Bowl.ma
