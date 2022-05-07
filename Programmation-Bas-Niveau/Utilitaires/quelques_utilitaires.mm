<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1365841749728" ID="ID_1410995526" MODIFIED="1365845437339">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      quelques utilitaires
    </p>
  </body>
</html>
</richcontent>
<node COLOR="#338800" CREATED="1365841768466" HGAP="26" ID="ID_1827986053" MODIFIED="1365845573944" POSITION="right" TEXT="cp1 f1 f2" VSHIFT="53">
<font BOLD="true" NAME="SansSerif" SIZE="12"/>
<icon BUILTIN="full-3"/>
<node CREATED="1365841786492" ID="ID_928790732" MODIFIED="1365841801661" TEXT="verifs">
<node CREATED="1365841804497" ID="ID_169688136" MODIFIED="1365841810907" TEXT="nombre d&apos;arguments"/>
<node CREATED="1365841813954" ID="ID_958489422" MODIFIED="1365841819627" TEXT="f1 est un fichier">
<node CREATED="1365841824268" ID="ID_1097531519" MODIFIED="1365842126531">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      stat == 0,<br />avec&#160;&#160;S_ISREG(st_mode)
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
<node CREATED="1365841830892" ID="ID_1490356980" MODIFIED="1365841836443" TEXT="f2 fichier ou absent">
<node CREATED="1365841967705" ID="ID_470691967" MODIFIED="1365842149738">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      idem, ou<br />stat renvoie -1
    </p>
    <p>
      et errno == ERRNOENT
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1365842170533" HGAP="51" ID="ID_804630091" MODIFIED="1365845387612" TEXT="actions" VSHIFT="4">
<node CREATED="1365842185412" ID="ID_446067784" MODIFIED="1365842213762">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      ouverture f1, f2<br />open() lecture &#233;criture
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1365842251172" ID="ID_1493153393" MODIFIED="1365842261042" TEXT="boucle read/write"/>
<node CREATED="1365842263699" ID="ID_202303758" MODIFIED="1365842266017" TEXT="close"/>
</node>
<node CREATED="1365842305618" ID="ID_1096828689" MODIFIED="1365842320526" TEXT="extension: cp f1 .. dest">
<node CREATED="1365842323494" ID="ID_1830325321" MODIFIED="1365842357430">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      si dest est un fichier,
    </p>
    <p>
      un seul fichier &#224; copier
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1365842362625" ID="ID_1835161036" MODIFIED="1365842509866">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      si dest est un r&#233;pertoire<br />copie sous m&#234;me nom de fichier<br />(apr&#232;s le dernier /)
    </p>
    <p>
      <br />
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node COLOR="#338800" CREATED="1365842545278" HGAP="2" ID="ID_1542241822" MODIFIED="1365845553049" POSITION="left" TEXT="cat fichier" VSHIFT="-58">
<font NAME="SansSerif" SIZE="10"/>
<icon BUILTIN="full-1"/>
<node CREATED="1365842566238" ID="ID_1820144968" MODIFIED="1365842630835" TEXT="verifs">
<node CREATED="1365842595792" ID="ID_126903256" MODIFIED="1365842624907" TEXT="nombre arguments"/>
</node>
<node CREATED="1365842744090" ID="ID_1147851911" MODIFIED="1365842781641" TEXT="actions">
<node CREATED="1365842752314" ID="ID_1961674866" MODIFIED="1365842757439" TEXT="open"/>
<node CREATED="1365842761546" ID="ID_1632196151" MODIFIED="1365842775959" TEXT="read(), write(1)"/>
<node CREATED="1365842783161" ID="ID_289085682" MODIFIED="1365842785547" TEXT="close"/>
</node>
<node CREATED="1365842923222" ID="ID_873636201" MODIFIED="1365842976776">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      extensions
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1365842631820" ID="ID_577691671" MODIFIED="1365842948729">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      verifier que
    </p>
    <p>
      f est un fichier
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1365842646287" ID="ID_1325648440" MODIFIED="1365842696718">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      stat == 0
    </p>
    <p>
      S_ISREG(st_mod)<br />
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1365843129074" ID="ID_295523416" MODIFIED="1365843142784" TEXT="cat [f ...]">
<node CREATED="1365843157154" ID="ID_1835971263" MODIFIED="1365843162576" TEXT="utilisation fd 0 "/>
</node>
</node>
</node>
<node COLOR="#669900" CREATED="1365844547382" HGAP="31" ID="ID_1928771703" MODIFIED="1365845560920" POSITION="left" TEXT="wc f" VSHIFT="-6">
<font NAME="SansSerif" SIZE="10"/>
<icon BUILTIN="full-2"/>
<node CREATED="1365844562550" ID="ID_1158373629" MODIFIED="1365844641162">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      boucle, avec comptage
    </p>
    <p>
      - des caract&#232;res
    </p>
    <p>
      - des retours charriot
    </p>
    <p>
      - des transitions nonlettre-&gt;lettre
    </p>
  </body>
</html>
</richcontent>
<node CREATED="1365844663188" ID="ID_956343188" MODIFIED="1365844706970" TEXT="open, read, wriie, close"/>
<node CREATED="1365844681555" ID="ID_900443536" MODIFIED="1365844684930" TEXT="isletter"/>
</node>
</node>
<node COLOR="#006633" CREATED="1365843102979" HGAP="11" ID="ID_1669931909" MODIFIED="1365845578272" POSITION="right" TEXT="ls f" VSHIFT="-94">
<font NAME="SansSerif" SIZE="10"/>
<icon BUILTIN="full-4"/>
<node CREATED="1365843233824" ID="ID_1622881864" MODIFIED="1365843290233">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      si f fichier,<br />&quot;%s est un fichier de taille %d&quot;
    </p>
  </body>
</html></richcontent>
<node CREATED="1365843361502" ID="ID_1355582623" MODIFIED="1365843490210">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      stat S_ISREG(st_mode)<br />
    </p>
    <p>
      + st_size
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1365843293839" HGAP="33" ID="ID_636131149" MODIFIED="1365845474819" VSHIFT="16">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      si f r&#233;pertoire
    </p>
    <p>
      &quot;%s est un r&#233;pertoire qui contient :
    </p>
    <p>
      + description des &#233;lements
    </p>
  </body>
</html></richcontent>
<node CREATED="1365843933442" ID="ID_1267041914" MODIFIED="1365843952967">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      opendir
    </p>
    <p>
      readdir
    </p>
    <p>
      closedir
    </p>
    <p>
      <br />
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
</map>
