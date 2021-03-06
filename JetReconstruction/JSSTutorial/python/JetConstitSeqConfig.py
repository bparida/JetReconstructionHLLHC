#########################################
##
## ClusterModConfig
##
#########################################

import JSSTutorial.RootCoreConfigInit

from ROOT import JetConstituentModSequence, CaloClusterConstituentsOrigin, SoftKillerWeightTool



class JetConstitSeqConfig(object):

    ## ###########################
    ## knownSequences contain the topLevel keywords defining a constituent sequence config.
    ## format is : 
    ##  "keyword" : ( ("inputContainer", "constituentType") , "modifierListAlias")
    ## or :
    ##  "keyword" : ( ("inputContainer", "constituentType") , ["modifierAlias1", "modifierAlias2",...] )
    ## in the 1st case, "modifierListAlias" must be an entry in knownModifierList
    ## in the 2nd case "modifierAlias1", "modifierAlias2",... are entries in knownModifierTools
    knownSequences = dict()

    ## #########################
    ## knownModifierList contain the keywords defining list of modifier tools
    ## format is :
    ##  "keyword" : ["modifierAlias1", "modifierAlias2",...]
    knownModifierList = dict()

    ## #########################
    ## knownModifierTools contain the keywords defining configuration of individual modifier tools.
    ## format is :
    ##  "keyword" : (ToolClass , dict_of_properties)
    knownModifierTools = dict()


    ## ###################################
    def constitModifSequence(self, name , inputContainer=None, modifierAlias=None, inputType=None,jetTool=None):
        """translates a keyword 'name' into a configured JetConstituentModSequence.
        this function uses the hiearchy defined by knownSequences, knownModifierList and knownModifierTools to perform the configuration.
        if additional parameters are given, they will overwrite those retrieved from knownXXX dictionnaries.

        returns the configured instance.
        """
        seqName = name+'Seq'

        if jetTool is None:
            jetTool = JetConstituentModSequence(seqName )
        else:
            jetTool.setName( seqName )

        # interpret arguments into options for JetConstituentModSequence

        # check if we know about name :
        (inputContainer_tmp, inputType_tmp), modifierAlias_tmp = self.knownSequences.get( name, ((None,None),None) )

        if inputContainer is None:
            inputContainer = inputContainer_tmp
        if inputType is None:
            inputType = inputType_tmp
        if modifierAlias is None:
            modifierAlias = modifierAlias_tmp
            
        outputContainer = name
        finalModList, modifAliasList = self.getModifList(modifierAlias)


        jetTool.InputContainer = inputContainer
        jetTool.OutputContainer = outputContainer
        jetTool.InputType = inputType
        jetTool.Modifiers = finalModList # pass the list of modifier we want 



        print " *********************************** "
        print " JetConstitSeqConfig : Configured cluster mod for ", name
        print "   --> alg name      : ",name.ljust(20)
        print "   --> modifiers     : ", str(modifierAlias).ljust(20), '=', modifAliasList
        print " *********************************** "

        return jetTool


    def getModifTool(self, alias,  **userProp ):
        klass , defaultProp = self.knownModifierTools.get( alias, (None,None) )
        if klass is None:
            print "ERROR. JetConstitSeqConfig.getModifTool unknown modifer  ",alias
            return None
        if userProp != {} : # copy default and update
            finalProp = dict(defaultProp)
            finalProp.update(userProp)
        else:
            finalProp = defaultProp

        modif = klass(alias, **finalProp)
        return modif

    def getModifList(self, alias, context=None):
        if isinstance(alias, list):
            aliasList = alias
        else:
            aliasList = self.knownModifierList.get(alias, None)
            if aliasList is None:
                print "ERROR JetConstitSeqConfig.getModifList unknown alias", failed
                print "            --> add it to JetConstitSeqConfig.knownModifierList ? "
                return
            
        toolList = []
        aliasList_str = []
        for a in aliasList:            
            if isinstance(a, str):
                t = self.getModifTool(a, context=context)
            else: # assume a is alaready a tool:
                t=a
                a=t.name()
            aliasList_str.append( a )
            toolList.append( t )
        return toolList, aliasList_str



JetConstitSeqConfig.knownSequences = {
    "OrigLCTopoClusters" : ( ("CaloCalTopoClusters","CaloCluster") , ['orig'] ),    
    "OrigSKLCTopoClusters" : ( ("CaloCalTopoClusters","CaloCluster") , ['orig','softkiller'] ),    
    }


JetConstitSeqConfig.knownModifierList = dict()

JetConstitSeqConfig.knownModifierTools = {
    'orig'       : (CaloClusterConstituentsOrigin , {} ),
    'softkiller' : (SoftKillerWeightTool, dict(SKGridSize=0.6) )

    }


constitConfig = JetConstitSeqConfig()
