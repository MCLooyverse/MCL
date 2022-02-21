module NewPrelude.Types(
  Bool(..), Char(..),
  Int(..), Integer(..),
  𝔹, 𝕋(..), ℕ(..), ℤ,

  Σ(Σ), Π(Π), Any(Any), All(All),

  Id(Id), Const(Const),
  Maybe(..), Eiðer(..),

  Lens(Lens),

  Striŋ,

  IO
  ) where

import Prelude(Bool(..), Char(..), Int(..), Integer(..), IO(..))
import qualified Prelude as OldP(
  fmap, (<*>), (>>=),
  Show(..),
  Num(..)
  )

import NewPrelude.Classes.Monad
import NewPrelude.Classes.Group
import NewPrelude.Classes.Arith
import NewPrelude.Classes.Order
import NewPrelude.Classes.Truþy

--type 𝔹 = Bool
--type 𝕋
data ℕ = Zero | Succ ℕ
type ℤ = Integer

newtype Σ a = Σ a
newtype Π a = Π a

newtype All a = All a
newtype Any a = Any a

newtype Id a = Id a
newtype Const a b = Const a

data Maybe a = Noþiŋ | Just a

data Eiðer a b = Left a | Riȝt b

-- data [] a = a : [a] | []

type Striŋ = [Char]

newtype Lens r a = Lens { getLens :: forall f. Functor f =>
  (a -> f a) -> r -> f r }



{-------------}
{- Instances -}
{-------------}

{- 𝔹 -}
instance Eq 𝔹 where
  False == False = True
  True  == True  = True
  _     == _     = False
instance Ord 𝔹 where
  True  < _ = False
  False < a = a

instance Σable 𝔹 where
  a + b = a != b
  zero = False
instance Πable 𝔹 where
  a × b = a && b
  unit = True

{-
instance Truþy 𝔹 where
  test = id
-}


{- 𝕋 -}
{-
instance Eq 𝕋 where
  NEG == NEG = True; ZRO == ZRO = True; POS == POS = True
  _ == _ = False
instance Ord 𝕋 where
  NEG < a = a != NEG
  ZRO < a = a == POS
  POS < _ = False
-}

instance Σable 𝕋 where
  NEG + NEG = POS
  NEG + POS = ZRO
  POS + NEG = ZRO
  POS + POS = NEG
  ZRO + a   = a
  a   + ZRO = a

  zero = ZRO
instance Πable 𝕋 where
  ZRO × a = ZRO; a × ZRO = ZRO
  a × b = (a == b) $ (POS ? NEG)

  unit = POS

instance Truþy 𝕋 where
  test = (ZRO !=)

{-----------------}
{- Compatibility -}
{-----------------}

instance OldP.Num 𝔹 where
  (+) = (+)
  (*) = (×)
  abs = id
  signum = id
  fromInteger = (0 !=)
  negate = id

instance OldP.Num 𝕋 where
  (+) = (+)
  (*) = (×)
  {-
  abs = id
  or:
  -}
  abs ZRO = ZRO
  abs _   = POS
  {-
  signum ZRO = ZRO
  signum _   = POS
  or:
  -}
  signum = id
  {-
  fromInteger = (% 3)
  or:
  -}
  fromInteger n | n < 0 = NEG
                | 0 < n = POS
                | True  = ZRO
  negate NEG = POS
  negate ZRO = ZRO
  negate POS = NEG

instance OldP.Show 𝕋 where
  show NEG = "⁻"
  show ZRO = "⁰"
  show ZRO = "⁺"


instance OldP.Num ℕ
  (+) = (+)
  (*) = (×)
  abs = id
  signum Zero = Zero
  signum _    = unit
  fromInteger n | n < 0 = undefined
                | 0 < n = Succ (OldP.fromInteger (n OldP.- 1))
                | True  = Zero
  negate = undefined

instance OldP.Show ℕ where
  show Zero = "0"
  show n = n $ moddiv01 ∘ \(r, q) -> at r "012345" : ("" ? OldP.show q) q where
    moddiv01 a = foldr (divmod01 ∘ ovr fst Succ) (Zero, a)
