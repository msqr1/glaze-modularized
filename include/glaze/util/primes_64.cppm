// Glaze Library
// For the license information refer to glaze.hpp

#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../../Export.hpp"
#include <array>
#include <cstdint>
#ifdef CPP_MODULES
export module glaze.util.primes_64;
#else
#endif




namespace glz
{
   // Array of random 64bit primes to avoid needing a generator
   // If you have a 10% chance of success, 128 tries has 1 : 719'380 odds of failure
   // formula: 1 / (1 - .10)^128
   // If you have a 15% chance of success, 128 tries has 1 : 1'082'374'392 odds of failure
   inline constexpr std::array<uint64_t, 128> primes_64 = {
      12835920395396008793ull, 15149911783463666029ull, 15211026597907833541ull, 14523965596842631817ull,
      16449355892475772073ull, 15002762636229733759ull, 12275448295353509891ull, 16826285440568349437ull,
      17433093378066653197ull, 10902769355249605843ull,
      // 10
      13434269760430048511ull, 11322871945166463571ull, 9764742595129026499ull, 13799666429485716229ull,
      14861204462552525359ull, 17599486090324515493ull, 10266842847898195667ull, 13468209895759219897ull,
      16289274021814922521ull, 17204791465022878523ull,
      // 20
      17650915497556268801ull, 9455725851336774341ull, 9961868820920778071ull, 18289017266131008167ull,
      16309921878298474091ull, 11652007405601517343ull, 17496906368504743207ull, 13339901080756288547ull,
      10018112158103183191ull, 14981853847663275059ull,
      // 30
      15024425770511821387ull, 10063189458099824779ull, 11839419318547724641ull, 12830508825440804579ull,
      18433073685722024387ull, 17299753196133391897ull, 15396274865347173053ull, 13749499465490568733ull,
      13860497513065316459ull, 11692484392508072123ull,
      // 40
      9438685344574842347ull, 14400973074801304571ull, 15991854874494707081ull, 12114831452910579989ull,
      13998562683662696077ull, 10851982863396796529ull, 10344539733475859441ull, 10045431121852560691ull,
      12186301656248163491ull, 10339340957932801343ull,
      // 50
      12602808298244447957ull, 9729322814141112953ull, 16362682788060189359ull, 14286005063617200559ull,
      10711312188467965759ull, 17189878401094383577ull, 14020292519311722517ull, 14345076507873302501ull,
      12604083410008146689ull, 13199781912416808047ull,
      // 60
      12315285542260457987ull, 9594690105092455043ull, 18319948908022195243ull, 16595976138570481823ull,
      12195274638706298323ull, 17646127793987855047ull, 16841966643138849923ull, 13507873747212661603ull,
      13643501673321416333ull, 12363547163076811279ull,
      // 70
      14884690672546139069ull, 16390599211964954609ull, 13389084014248465909ull, 9833412254409620477ull,
      13398707790907619797ull, 18368581595698861159ull, 10384836406878147059ull, 9453231669972318281ull,
      16669513057697818169ull, 14697852657232879237ull,
      // 80
      15363091209268144241ull, 15275124567630446861ull, 17481357028816037011ull, 12534821792295694231ull,
      11054303650520058359ull, 12403322865831490261ull, 16889743306920098983ull, 16047403249754946029ull,
      16775982981238529423ull, 12421181800577384167ull,
      // 90
      9280311361047996317ull, 12160582891762080001ull, 17367939315478490407ull, 9267482598791369377ull,
      17806662591996060709ull, 11533875385674872861ull, 16816712667689633689ull, 16223588510861656927ull,
      13482535659370429831ull, 11801382448764686461ull,
      // 100
      18177646705946605939ull, 12608957628213527767ull, 17302819561726521227ull, 10609776890453861677ull,
      16615779974080376533ull, 14779379909309032351ull, 14673741062489338759ull, 11634351264868983527ull,
      13874971253878591537ull, 17332275173558136899ull,
      // 110
      11257300840627829851ull, 13341443249676872783ull, 11607230252125083613ull, 12141161410409106457ull,
      13282325402819801929ull, 17990774082148480601ull, 15496227723025164119ull, 15956314649183876369ull,
      9834926670622290883ull, 16435035491439552943ull,
      // 120
      14806063675962222449ull, 18113370406266068597ull, 9968958022058734229ull, 14864844583184822773ull,
      11170341707334307859ull, 10502344452987841991ull, 16247553219265957739ull, 14933089789266129581ull};
}
