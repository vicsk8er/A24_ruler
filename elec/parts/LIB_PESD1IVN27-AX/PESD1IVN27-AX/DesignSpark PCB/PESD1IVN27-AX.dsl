SamacSys ECAD Model
1370356/875189/2.50/2/2/Diode ESD Bi-directional

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r110_50"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.5) (shapeHeight 1.1))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "SOD2512X110N" (originalName "SOD2512X110N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r110_50) (pt -1.15, 0) (rotation 90))
			(pad (padNum 2) (padStyleRef r110_50) (pt 1.15, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.975 1.15) (pt 1.975 1.15) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.975 1.15) (pt 1.975 -1.15) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.975 -1.15) (pt -1.975 -1.15) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.975 -1.15) (pt -1.975 1.15) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.85 0.625) (pt 0.85 0.625) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.85 0.625) (pt 0.85 -0.625) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.85 -0.625) (pt -0.85 -0.625) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.85 -0.625) (pt -0.85 0.625) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.85 0.075) (pt -0.3 0.625) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.7 0.625) (pt 0.85 0.625) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.85 -0.625) (pt 0.85 -0.625) (width 0.2))
		)
	)
	(symbolDef "PESD1IVN27-AX" (originalName "PESD1IVN27-AX")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 0 mils -45 mils) (rotation 0]) (justify "UpperLeft") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 800 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 800 mils -45 mils) (rotation 0]) (justify "UpperRight") (textStyleRef "Default"))
		))
		(line (pt 400 mils 0 mils) (pt 200 mils -100 mils) (width 6 mils))
		(line (pt 200 mils -100 mils) (pt 200 mils 100 mils) (width 6 mils))
		(line (pt 200 mils 100 mils) (pt 400 mils 0 mils) (width 6 mils))
		(line (pt 400 mils 0 mils) (pt 600 mils -100 mils) (width 6 mils))
		(line (pt 600 mils -100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 400 mils 0 mils) (width 6 mils))
		(line (pt 400 mils -180 mils) (pt 400 mils 180 mils) (width 6 mils))
		(line (pt 440 mils 200 mils) (pt 400 mils 180 mils) (width 6 mils))
		(line (pt 400 mils -180 mils) (pt 360 mils -200 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 600 mils 350 mils) (justify LowerLeft) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "PESD1IVN27-AX" (originalName "PESD1IVN27-AX") (compHeader (numPins 2) (numParts 1) (refDesPrefix D)
		)
		(compPin "1" (pinName "K1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "K2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "PESD1IVN27-AX"))
		(attachedPattern (patternNum 1) (patternName "SOD2512X110N")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Mouser Part Number" "771-PESD1IVN27-AX")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Nexperia/PESD1IVN27-AX?qs=0lQeLiL1qyYTtxrCfdJstQ%3D%3D")
		(attr "Manufacturer_Name" "Nexperia")
		(attr "Manufacturer_Part_Number" "PESD1IVN27-AX")
		(attr "Description" "ESD Suppressors / TVS Diodes ESD protection for In-vehicle networks")
		(attr "Datasheet Link" "https://assets.nexperia.com/documents/data-sheet/PESD1IVN27-A.pdf")
		(attr "Height" "1.1 mm")
	)

)
