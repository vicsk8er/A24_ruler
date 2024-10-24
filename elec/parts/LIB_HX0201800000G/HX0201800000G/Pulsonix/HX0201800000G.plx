PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//18552413/875189/2.50/4/3/Connector

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c210_h140"
		(holeDiam 1.4)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 2.100) (shapeHeight 2.100))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 2.100) (shapeHeight 2.100))
	)
	(padStyleDef "s210_h140"
		(holeDiam 1.4)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 2.100) (shapeHeight 2.100))
		(padShape (layerNumRef 16) (padShapeType Rect)  (shapeWidth 2.100) (shapeHeight 2.100))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "HX0201800000G" (originalName "HX0201800000G")
		(multiLayer
			(pad (padNum 1) (padStyleRef s210_h140) (pt 0.000, 0.000) (rotation 90))
			(pad (padNum 2) (padStyleRef c210_h140) (pt 0.000, 5.000) (rotation 90))
			(pad (padNum 3) (padStyleRef c210_h140) (pt 5.000, 0.000) (rotation 90))
			(pad (padNum 4) (padStyleRef c210_h140) (pt 5.000, 5.000) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 2.300, 5.150) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.4 12.9) (pt 8 12.9) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 8 12.9) (pt 8 -2.6) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 8 -2.6) (pt -3.4 -2.6) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.4 -2.6) (pt -3.4 12.9) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.4 12.9) (pt 8 12.9) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 8 12.9) (pt 8 -2.6) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 8 -2.6) (pt -3.4 -2.6) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.4 -2.6) (pt -3.4 12.9) (width 0.2))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -4.4 13.9) (pt 9 13.9) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 9 13.9) (pt 9 -3.6) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 9 -3.6) (pt -4.4 -3.6) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -4.4 -3.6) (pt -4.4 13.9) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.9 0) (pt -3.9 0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -3.95, 0) (radius 0.05) (startAngle .0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -4 0) (pt -4 0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -3.95, 0) (radius 0.05) (startAngle 180.0) (sweepAngle 180.0) (width 0.1))
		)
	)
	(symbolDef "HX0201800000G" (originalName "HX0201800000G")

		(pin (pinNum 1) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 800 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 570 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 800 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 570 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 650 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "HX0201800000G" (originalName "HX0201800000G") (compHeader (numPins 4) (numParts 1) (refDesPrefix J)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "3") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "4" (pinName "4") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "HX0201800000G"))
		(attachedPattern (patternNum 1) (patternName "HX0201800000G")
			(numPads 4)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
			)
		)
		(attr "Mouser Part Number" "649-HX02018000J0G")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Amphenol-Anytek/HX0201800000G?qs=Mv7BduZupUjWRzKlnc0xpw%3D%3D")
		(attr "Manufacturer_Name" "Amphenol")
		(attr "Manufacturer_Part_Number" "HX0201800000G")
		(attr "Description" "Fixed Terminal Blocks TB SPRING CLAMP 180D")
		(attr "<Hyperlink>" "")
		(attr "<Component Height>" "12.8")
		(attr "<STEP Filename>" "HX0201800000G.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)
