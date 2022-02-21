module BinTypes (
  Absurd, Boring(singVal),
  absurd, boring ) where

  import Prelude()
  import NewPrelude.Types
  import NewPrelude.GenericValues

  data Void

  class Absurd a
  class Boring b where
    singVal :: b

  absurd :: Absurd a => a -> b
  absurd = const undefined
  boring :: Boring b => a -> b
  boring = const singVal


  instance Absurd a => Absurd (i -> a)
  instance Absurd a => Absurd (Id a)
  instance Absurd a => Absurd (Const a b)

  instance Absurd Void where
    absurd = const undefined
  instance (Absurd a, Absurd b) => Absurd (Eiðer a b)


  instance Boring b => Boring (i -> b) where
    singVal = boring
  instance Boring b => Boring (Id b) where
    singVal = Id singVal
  instance Boring b => Boring (Const b c) where
    singVal = Const singVal

  instance Boring () where
    singVal = ()
  instance Absurd a => Boring (a -> r) where
    singVal = absurd
  instance Absurd a => Boring (Maybe a) where
    singVal = Noþiŋ
  instance Absurd a => Boring [a] where
    singVal = []
  instance (Absurd a, Boring b) => Boring (Eiðer a b) where
    singVal = Riȝt singVal
  instance (Absurd a, Boring b) => Boring (Eiðer b a) where
    singVal = Left singVal
